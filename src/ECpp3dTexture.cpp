/*
 * ECpp3dTexture.cpp
 *
 *  Created on: 01/12/2012
 *      Author: christian
 */


#include "handlers/ECpp3dTexture.h"
#include "ECpp3dOpenGLContext.h"
#include <jpeglib.h>

namespace ECpp3d {


Texture::Texture(GLuint location)
	: OpenGLHandler(location), type(0), bindtype(0){
	sampler = 0;
}

Texture::Texture(GLuint location,GLenum type, GLenum bindtype)
	: OpenGLHandler(location), type(type), bindtype(bindtype) {
	sampler = 0;
}

Textures Texture::generateTextures(GLsizei number){
	GLuint locations[number];
	glGenTextures(number,locations);

	Textures textures;

	for(int i = 0; i < number; ++i) {
		Texture * ntextures = new Texture(locations[i]);
		textures.push_back(ntextures);
	}

	return textures;
}

void Texture::initialize() {
	Texture::ensureSampler();
}

void Texture::ensureSampler(){
	if(!sampler) {
		sampler = OpenGLContext::getSampler();
		sampler->ensureActive();
		glBindTexture(type,location);
	}
}

Texture * Texture::generateTexture(){
	return generateTextures(1)[0];
}

void Texture::finalize() {
	glDeleteTextures(1,&location);
	OpenGLContext::free(sampler);
}

void Texture::attach(const Uniform & u) {
	ensureSampler();
	assert(u.getType() == bindtype);
	glUniform1i(u.getIndex(),sampler->getActiveId());
}

void Texture::setBaseLevel(GLint level) {
	setParameter(GL_TEXTURE_BASE_LEVEL,level);
}

void Texture::setMaxLevel(GLint level) {
	setParameter(GL_TEXTURE_MAX_LEVEL,level);
}

void Texture::setMagnifyMethod(GLenum method) {
	setParameter(GL_TEXTURE_MAG_FILTER,method);
}

void Texture::setMinimizeMethod(GLenum method) {
	setParameter(GL_TEXTURE_MIN_FILTER,method);
}

const std::string Texture::toString() const {
	std::stringstream s;
	s << "<Texture at ["<< location << "] - sampler: " << sampler <<">";
	return s.str();
}


void Texture::setWrappingS(GLenum method) {
	setParameter(GL_TEXTURE_WRAP_S,method);
}
void Texture::setWrappingT(GLenum method) {
	setParameter(GL_TEXTURE_WRAP_T,method);
}
void Texture::setWrappingR(GLenum method) {
	setParameter(GL_TEXTURE_WRAP_R,method);
}


// Sampler

void Sampler::ensureActive() const{
	glActiveTexture(getActiveEnum());
}

GLuint Sampler::getActiveId() const {
	return activeid;
}

const std::string Sampler::toString() const {
	std::stringstream s;
	s << "<Sampler at ["<< activeid << "]>";
	return s.str();
}

Samplers Sampler::getSamplers() {
	GLuint num_samplers = OpenGLContext::getMaxCombinedTextureImageUnits();

	Samplers samplers;
//	samplers.push_back(new Sampler(0));
	for(int i = 0; i < num_samplers-1; ++i)
		samplers.push_back(new Sampler(i));

	return samplers;
}

// Texture 1D


void Texture1D::initialize(const std::vector<glm::vec4> & data)  {
	Texture::initialize();
	glTexImage1D(type,0,GL_RGBA,data.size(),0,GL_RGBA,GL_FLOAT,&data[0]);
	setBaseLevel(0);
	setMaxLevel(0);
}

Texture1D * Texture1D::createLinearGradient(Texture * texture,int size, const gradient & description ) {
	std::vector<glm::vec4> data;
	int index = 0;
	float now = 0, stripsize = description[1].first;
	for(int i = 0; i < size; i++) {
		float value = ((float) i ) / size;
		if(value > stripsize + now) {
			index ++;
			now = description[index].first;
			stripsize = description[index+1].first - now;
		}
		float part = (value - now) / stripsize;
		glm::vec4 color = description[index].second * (1-part) + description[index+1].second * part;
		data.push_back(color);
	}
	Texture1D * retex = new Texture1D(texture);
	retex->initialize(data);
	return retex;
}
// Texture 2D


GLenum Texture2D::getBindType() const{
	return bindtype;
}



void Texture2D::initialize(GLint internalformat,const std::string & filename) throw (IOException) {
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	JSAMPROW row_pointer[1];

	FILE * infile = fopen(filename.c_str(),"rb");
	if(!infile) throw IOException("Could not find file: " + filename);

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress((j_decompress_ptr) &cinfo);
	jpeg_stdio_src( &cinfo, infile );
	jpeg_read_header( &cinfo, 1 );

	jpeg_start_decompress( &cinfo );

	GLsizei width = cinfo.output_width;
	GLsizei height = cinfo.output_height;
	int num = cinfo.output_components;

	GLubyte * image = new GLubyte[width*height*num];

	GLenum format;

	switch(num) {
		case (1): format = GL_R8; break;
		case (3): format = GL_RGB; break;
		case (4): format = GL_RGBA; break;
		default :
			throw Exception("Not Know format of loaded image, or it is empty");
	}

	row_pointer[0] = (unsigned char *)malloc(width*num);
	int location = 0;
	while( cinfo.output_scanline < cinfo.image_height )
	{
		jpeg_read_scanlines( &cinfo, row_pointer, 1 );
		for(int i=0; i<cinfo.image_width*cinfo.num_components;i++)
			image[location++] = row_pointer[0][i];
	}

	jpeg_finish_decompress( &cinfo );
	jpeg_destroy_decompress( &cinfo );
	free( row_pointer[0] );
	fclose( infile );

	Texture2D::initialize(internalformat,width,height,format,GL_UNSIGNED_BYTE,image);
	delete image;
}

void Texture2D::initialize(GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels) {
	Texture::initialize();
	glTexImage2D(this->type,0,internalformat,width,height,0,format,type,pixels);
	setBaseLevel(0);
	setMaxLevel(0);
}

void Texture2D::initialize(GLint internalformat, GLsizei width, GLsizei height) {
	initialize(internalformat,width,height,GL_RGBA,GL_FLOAT,0);
}

}
