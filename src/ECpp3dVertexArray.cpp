/*
 * ECpp3dVertexAttributeArray.cpp
 *
 *  Created on: 25/11/2012
 *      Author: christian
 */

#include "ECpp3dVertexArray.h"

namespace ECpp3d {

GLuint VertexArray::bound = 0;


std::vector<VertexArray> VertexArray::generateVertexArrays(GLsizei size) {
	GLuint locations[size];
	glGenVertexArrays(size,locations);
	std::vector<Buffer> buffers = Buffer::generateBuffers(size);
	std::vector<VertexArray> arrays;
	for(int i = 0; i < size; ++i)
		arrays.push_back(VertexArray(buffers[i],locations[i]));

	return arrays;
}

VertexArray VertexArray::generateVertexArray() {
	return generateVertexArrays(1)[0];
}



VertexArray::~VertexArray() {

}

VertexArray::VertexArray() {
	vert_size = 0;
	location = -1;
	number_of_vertices = 0;
	buffer = ArrayBuffer();

}

VertexArray::VertexArray(const ArrayBuffer & buffer,GLuint location) {
	this->buffer = ArrayBuffer(buffer);
	this->location = location;
	vert_size = 0;
	number_of_vertices = 0;
}


void VertexArray::ensureBound() const{
	if(bound != location) {
		bound == location;
		glBindVertexArray(location);
	}
}

void VertexArray::initialize(int vector_size, int vertices){
	ensureBound();
	vert_size = vector_size;
	number_of_vertices = vertices;
	buffer.initialize(NULL,vert_size*number_of_vertices*4,GL_STATIC_DRAW);
}

void VertexArray::initialize(int vector_size, int vertices,const GLfloat * data){
	std::cout << location << std::endl;
	ensureBound();
	vert_size = vector_size;
	number_of_vertices = vertices;
	buffer.initialize(data,vert_size*number_of_vertices*4,GL_STATIC_DRAW);
}

void VertexArray::finalize() {
	glDeleteVertexArrays(1,&location);
	buffer.finalize();
}

void VertexArray::validate() const throw (OpenGLException){
	buffer.validate();
}

void VertexArray::attach(int pos) const{
	ensureBound();
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos,vert_size,GL_FLOAT,GL_FALSE,0,0);
}

}
