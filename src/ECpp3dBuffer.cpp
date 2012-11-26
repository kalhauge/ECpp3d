/*
 * ECpp3dBuffer.cpp
 *
 *  Created on: 26/11/2012
 *      Author: christian
 */

#include "ECpp3dBuffer.h"

namespace ECpp3d {

const ArrayBuffer * ArrayBuffer::bound = NULL;

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
}

Buffer::Buffer(GLuint location) {
	this->location = location;
}

void Buffer::initialize(GLenum target, const GLvoid * data,GLsizei size, GLenum hint) {
	this->size = size;
	glBufferData(target,size,data,hint);
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
	if(bound != this) {
		bound == this;
		glBindBuffer(GL_ARRAY_BUFFER,location);
	}
}

}
