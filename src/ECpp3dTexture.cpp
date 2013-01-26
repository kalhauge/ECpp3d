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


void Texture::setupTexture(){
	sampler = 0;
    data = 0;
}

Texture::~Texture(){
    if(data) delete data;
}

Texture::Texture(GLuint location) : OpenGLHandler(location), type(0), bindtype(0){
	setupTexture();
}

Texture::Texture(GLuint location,GLenum type, GLenum bindtype)
	: OpenGLHandler(location), type(type), bindtype(bindtype) {
	setupTexture();
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

GLsizei Texture::getWidth() {
	return data->getSize().width;
}

GLsizei Texture::getHeight() {
	return data->getSize().height;
}

GLsizei Texture::getDepth() {
	return data->getSize().depth;
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

void Texture1D::pushImage() {
    ensureSampler();
    glTexImage1D(type,0,format,getWidth(),0,data->getFormat(),data->getType(),data->getData());
	
}

Texture1D * Texture1D::initialize(Image * image, GLint internalformat) {
	Texture::initialize();
    this->format = internalformat;
    this->data = image;
    pushImage();
	setBaseLevel(0);
	setMaxLevel(0);
    return this;
}

Texture1D * Texture1D::create(Texture * const texture) {
    return new Texture1D(texture);
}
// Texture 2D


GLenum Texture2D::getBindType() const{
	return bindtype;
}

void Texture2D::pushImage() {
    ensureSampler();
    glTexImage2D(type,0,format,getWidth(),getHeight(),0,data->getFormat(),data->getType(),data->getData());
	
}

Texture2D * Texture2D::initialize(Image * image, GLint internalformat) {
    Texture::initialize();
    this->data = image;
    this->format = internalformat;
    pushImage();
    setBaseLevel(0);
	setMaxLevel(0);
    return this;

}

Texture2D * Texture2D::initialize(const std::string & filename,GLint internalformat) throw (IOException) {
    return initialize(Image::fromJPEG(filename),internalformat);
}

Texture2D * Texture2D::initialize(GLsizei width, GLsizei height, GLint internalformat) {
	return initialize(new Image(makeImageSize(width,height,1)),internalformat);
}

GLsizei TextureCube::getWidth() {
	return sides[0]->getSize().width;
}

GLsizei TextureCube::getHeight() {
	return sides[0]->getSize().height;
}

GLsizei TextureCube::getDepth() {
	return sides[0]->getSize().depth;
}

Texture2D * Texture2D::create(Texture * const texture) {
    return new Texture2D(texture);
}

// TextureCube

TextureCube * TextureCube::initialize(Image * sides[6], GLint internalformat) {
	Texture::initialize();
	memcpy(this->sides,sides,sizeof(Image*)*6);
	for(int i = 0; i < 6; i++) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,0,
					internalformat,
					getWidth(),getHeight(),
					0,sides[i]->getFormat(),
					GL_FLOAT,sides[i]->getData());
	}
    return this;
}

TextureCube * TextureCube::create(Texture * const texture) {
    return new TextureCube(texture);
}

}
