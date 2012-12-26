/*
 * ECpp3dBuffer.cpp
 *
 *  Created on: 26/11/2012
 *      Author: christian
 */

#include "handlers/ECpp3dBuffer.h"
#include "ECpp3dOpenGLContext.h"
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
	s << "<Buffer at [" << location << "] - size: " << size << " usage: " << usage << ">";
	return s.str();
}

void Buffer::initialize(GLenum target, const GLvoid * data,GLsizeiptr size,GLenum type, GLenum usage) {
	this->type = type;
	this->size = size * OpenGLContext::getSizeOf(type);
	this->usage = usage;
	glBufferData(target,this->size,data,usage);
}

GLint Buffer::getServerInfo(GLenum target, GLenum e) const{
	GLint result = -1;
	glGetBufferParameteriv(target,e,&result);
	return result;
}

GLint ArrayBuffer::getServerInfo(GLenum e) const{
	bind();
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

void ArrayBuffer::initialize(const GLvoid * data,GLsizeiptr numberOfVerts,GLsizeiptr vertSize,GLenum type,GLenum hint){
	bind();
	this->vertSize = vertSize;
	this->numberOfVerts = numberOfVerts;
	Buffer::initialize(GL_ARRAY_BUFFER,data,numberOfVerts*vertSize,type,hint);
}

void ArrayBuffer::setData(GLintptr at, const GLvoid * data, GLsizei size) {
	bind();
	Buffer::setData(GL_ARRAY_BUFFER,at,data,size);
}

void ArrayBuffer::attach(int location) const{
	bind();
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location,vertSize,type,false,0,0);
}

void ArrayBuffer::bind(bool force) const{
	if(bound != this || force) {
		bound = this;
		glBindBuffer(GL_ARRAY_BUFFER,location);
	}
}

}
