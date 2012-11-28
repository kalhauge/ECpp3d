/*
 * ECpp3dBuffer.cpp
 *
 *  Created on: 26/11/2012
 *      Author: christian
 */

#include "ECpp3dBuffer.h"

namespace ECpp3d {

GLuint ArrayBuffer::bound = NULL;

std::vector<Buffer> Buffer::generateBuffers(GLsizei number){
	GLuint locations[number];
	glGenBuffers(number,locations);

	std::vector<Buffer> buffers;

	for(int i = 0; i < number; ++i)
		buffers.push_back(Buffer(locations[i]));

	return buffers;
}

Buffer Buffer::generateBuffer(){
	return generateBuffers(1)[0];
}

Buffer::Buffer() {
	this->location = -1;
	this->size = 0;
	this->usage = 0;
}

Buffer::Buffer(GLuint location) {
	this->location = location;
	this->size = 0;
	this->usage = 0;
}

void Buffer::initialize(GLenum target, const GLvoid * data,GLsizei size, GLenum usage) {
	this->size = size;
	this->usage = usage;
	glBufferData(target,size,data,usage);
}

GLint Buffer::getServerInfo(GLenum e) const{
	GLint result;
	glGetBufferParameteriv(location,e,&result);
	return result;
}

void Buffer::validate() const throw (OpenGLException) {
	GLint value = getServerInfo(GL_BUFFER_SIZE);
	if(size != value)
		throw OpenGLInconsistentStateException(this,"size",(GLint) size, value);

	value = getServerInfo(GL_BUFFER_USAGE);
	if(usage != value)
		throw OpenGLInconsistentStateException(this,"usage",(GLint) usage,value);

}

void Buffer::finalize() {
	glDeleteBuffers(1,&location);
}

void Buffer::setData(GLenum target, GLintptr at, const GLvoid * data, GLsizei size) {
	glBufferSubData(target,at,size,data);
}

ArrayBuffer::ArrayBuffer(const Buffer & buffer) {
	this->location = buffer.getLocation();
}

ArrayBuffer::ArrayBuffer() {
	this->location = -1;
}



void ArrayBuffer::initialize(const GLvoid * data,GLsizei size,GLenum hint){
	ensureBound();
	Buffer::initialize(GL_ARRAY_BUFFER,data,size,hint);
}

void ArrayBuffer::setData(GLintptr at, const GLvoid * data, GLsizei size) {
	ensureBound();
	Buffer::setData(GL_ARRAY_BUFFER,at,data,size);
}

void ArrayBuffer::ensureBound() const{
	if(bound != location) {
		bound == location;
		glBindBuffer(GL_ARRAY_BUFFER,location);
	}
}

}
