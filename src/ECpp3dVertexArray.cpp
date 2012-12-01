/*
 * ECpp3dVertexAttributeArray.cpp
 *
 *  Created on: 25/11/2012
 *      Author: christian
 */

#include "handlers/ECpp3dVertexArray.h"

namespace ECpp3d {

const VertexArray * VertexArray::bound = 0;


VertexArrays VertexArray::generateVertexArrays(GLsizei size) {
	GLuint locations[size];
	glGenVertexArrays(size,locations);
	Buffers buffers = Buffer::generateBuffers(size);
	VertexArrays arrays;
	for(int i = 0; i < size; ++i) {
		ArrayBuffer * buffer = new ArrayBuffer(buffers[i]);
		VertexArray * narray = new VertexArray(buffer,locations[i]);
		arrays.push_back(narray);
		delete buffers[i];
	}

	return arrays;
}

VertexArray * VertexArray::generateVertexArray() {
	return generateVertexArrays(1)[0];
}

VertexArray::~VertexArray() {

}


void VertexArray::ensureBound() const{
	if(bound != this) {
		bound = this;
		glBindVertexArray(location);
	}
}

void VertexArray::initialize(int vector_size, int vertices){
	initialize(vector_size,vertices,0);
}

void VertexArray::initialize(int vector_size, int vertices,const GLfloat * data){
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
