//
//  ECpp3dImage.cpp
//  ECpp3d
//
//  Created by Christian Gram Kalhauge on 22/01/13.
//
//

#include "tools/ECpp3dImage.h"
#include <jpeglib.h>
#include <vector>

namespace ECpp3d {


ImageSize makeImageSize(GLsizei width,GLsizei height,GLsizei depth) {
    return (ImageSize) {width,height,depth};
}

Image::Image(ImageSize size) {
    this->size = size;
    this->format = GL_RGBA;
    this->type = GL_BYTE;
    this->data = 0;
}

Image::Image(ImageSize size, GLenum data_format, GLenum data_type) {
    this->size = size;
    this->format = data_format;
    this->type = data_type;
    this->data = 0;
}

Image::~Image() {
    clearSpace();
}

GLenum Image::getFormat() {
    return format;
}
GLenum Image::getType(){
    return type;
}

const ImageSize & Image::getSize() {
    return size;
}

const GLubyte * Image::getData() {
    return data;
}


Image * Image::fromJPEG(const std::string & filename)
    throw (IOException){
    
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

	GLenum format;

	switch(num) {
		case (1): format = GL_R8; break;
        case (2): format = GL_RG; break;
		case (3): format = GL_RGB; break;
		case (4): format = GL_RGBA; break;
		default :
			throw Exception("Trying to load an unknown format, or the image is empty");
	}
    
    Image * image = new Image(makeImageSize(width,height,1),format, GL_UNSIGNED_BYTE);
    image->allocateSpace();
	row_pointer[0] = (unsigned char *)malloc(width*num);
	int location = 0;
	while( cinfo.output_scanline < cinfo.image_height )
	{
		jpeg_read_scanlines( &cinfo, row_pointer, 1 );
		for(int i=0; i<cinfo.image_width*cinfo.num_components;i++)
			image->data[location++] = row_pointer[0][i];
	}

	jpeg_finish_decompress( &cinfo );
	jpeg_destroy_decompress( &cinfo );
	free( row_pointer[0] );
	fclose( infile );
    
    return image;
}

Image * Image::fromGradient(GLint width, const gradient & gradient) {
    std::vector<glm::vec4> data;
    int index = 0;
	float now = 0, stripsize = gradient[1].first;
	for(int i = 0; i < width; i++) {
		float value = ((float) i ) / width;
		if(value > stripsize + now) {
			index ++;
			now = gradient[index].first;
			stripsize = gradient[index+1].first - now;
		}
		float part = (value - now) / stripsize;
		glm::vec4 color = gradient[index].second * (1-part) + gradient[index+1].second * part;
		data.push_back(color);
	}
    Image * image = new Image(makeImageSize(width,1,1),GL_RGBA,GL_FLOAT);
    image->allocateSpace();
    memcpy(image->data,&data[0],data.size()*sizeof(glm::vec4));
    return image;
    
}

void Image::allocateSpace() {
    clearSpace();
    data = new GLubyte[typeSize(type)*formatSize(format)*size.width * size.height * size.depth];
}


void Image::clearSpace() {
    if(data) delete [] data;
}





}