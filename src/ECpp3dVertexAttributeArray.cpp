/*
 * ECpp3dVertexAttributeArray.cpp
 *
 *  Created on: 25/11/2012
 *      Author: christian
 */

#include "ECpp3dVertexAttributeArray.h"

namespace ECpp3d {

std::vector<VertexAttributeArray> VertexAttributeArray::generateVertexArrays(GLsizei size) {
	GLuint locations[size];
	glGenVertexArrays(size,locations);
	std::vector<Buffer> buffers = Buffer::generateBuffers(size);
	std::vector<VertexAttributeArray> arrays;
	for(int i = 0; i < size; ++i)
		arrays.push_back(VertexAttributeArray(buffers[i],locations[i]));

	return arrays;
}

VertexAttributeArray VertexAttributeArray::generateVertexArray() {
	return generateVertexArrays(1)[0];
}



VertexAttributeArray::~VertexAttributeArray() {

}

VertexAttributeArray::VertexAttributeArray() {
	vert_size = 0;
	location = -1;
	number_of_vertices = 0;
	buffer = ArrayBuffer();

}

VertexAttributeArray::VertexAttributeArray(const ArrayBuffer & buffer,GLuint location) {
	this->buffer = ArrayBuffer(buffer);
	this->location = location;
	vert_size = 0;
	number_of_vertices = 0;
}

const VertexAttributeArray * VertexAttributeArray::bound = NULL;

void VertexAttributeArray::ensureBound() const{
	if(bound != this) {
		bound = this;
		glBindVertexArray(location);
	}
}

void VertexAttributeArray::initialize(int vector_size, int vertices){
	ensureBound();
	vert_size = vector_size;
	number_of_vertices = vertices;
	buffer.initialize(NULL,vert_size*number_of_vertices*4,GL_STATIC_DRAW);
}

void VertexAttributeArray::initialize(int vector_size, int vertices,const GLfloat * data){
	std::cout << location << std::endl;
	ensureBound();
	vert_size = vector_size;
	number_of_vertices = vertices;
	buffer.initialize(data,vert_size*number_of_vertices*4,GL_STATIC_DRAW);
}

void VertexAttributeArray::finalize() {
	glDeleteVertexArrays(1,&location);
	buffer.finalize();
}

void VertexAttributeArray::attach(int pos) const{
	ensureBound();
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos,vert_size,GL_FLOAT,GL_FALSE,0,0);
}

}
