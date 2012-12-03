/*
 * ECpp3dBuffer.cpp
 *
 *  Created on: 26/11/2012
 *      Author: christian
 */

#include "handlers/ECpp3dBuffer.h"

namespace ECpp3d {

const ArrayBuffer * ArrayBuffer::bound = 0;

Buffers Buffer::generateBuffers(GLsizei number){
	GLuint locations[number];
	glGenBuffers(number,locations);

	Buffers buffers;

	for(int i = 0; i < number; ++i) {
		Buffer * nbuffer = new Buffer(locations[i]);
		buffers.push_back(nbuffer);
	}

	return buffers;
}

Buffer * Buffer::generateBuffer(){
	return generateBuffers(1)[0];
}

const std::string Buffer::toString() const {
	std::stringstream s;
	s << "<Buffer: location: " << location << " size: " << size << " usage: " << usage << ">";
	return s.str();
}

void Buffer::initialize(GLenum target, const GLvoid * data,GLsizeiptr size, GLenum usage) {
	this->size = size;
	this->usage = usage;
	glBufferData(target,size,data,usage);
}

GLint Buffer::getServerInfo(GLenum target, GLenum e) const{
	GLint result = -1;
	glGetBufferParameteriv(target,e,&result);
	return result;
}

GLint ArrayBuffer::getServerInfo(GLenum e) const{
	ensureBound();
	return Buffer::getServerInfo(GL_ARRAY_BUFFER,e);

}


void ArrayBuffer::validate() const throw (OpenGLException) {
	GLint value = getServerInfo(GL_BUFFER_SIZE);
	OpenGLContext::checkForErrors();
	if(size != value)
		throw OpenGLInconsistentStateException(this,"size",GLint(size), value);

	value = getServerInfo(GL_BUFFER_USAGE);
	if(usage != value)
		throw OpenGLInconsistentStateException(this,"usage",GLint(usage),value);

}

void Buffer::finalize() {
	glDeleteBuffers(1,&location);
}

void Buffer::setData(GLenum target, GLintptr at, const GLvoid * data, GLsizei size) {
	glBufferSubData(target,at,size,data);
}

void ArrayBuffer::initialize(const GLvoid * data,GLsizeiptr size,GLenum hint){
	ensureBound();
	Buffer::initialize(GL_ARRAY_BUFFER,data,size,hint);
}

void ArrayBuffer::setData(GLintptr at, const GLvoid * data, GLsizei size) {
	ensureBound();
	Buffer::setData(GL_ARRAY_BUFFER,at,data,size);
}

void ArrayBuffer::ensureBound() const{
	if(bound != this) {
		bound = this;
		glBindBuffer(GL_ARRAY_BUFFER,location);
	}
}

}
