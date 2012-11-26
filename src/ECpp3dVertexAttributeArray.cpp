/*
 * ECpp3dVertexAttributeArray.cpp
 *
 *  Created on: 25/11/2012
 *      Author: christian
 */

#include "ECpp3dVertexAttributeArray.h"

namespace ECpp3d {

VertexAttributeArray::~VertexAttributeArray() {
	delete[] data;
}

void VertexAttributeArray::init(int vector_size, int vertices){
	data = new GLfloat[vector_size*vertices];
	size = vector_size;
	number_of_vertices = vertices;
}

void VertexAttributeArray::setup(){

	GLuint vertexArrayObject;
	GLuint vertexBuffer;

	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER,size * number_of_vertices * 4, data, GL_STATIC_DRAW);


}

VertexAttributeArray::VertexAttributeArray(const std::vector<glm::vec4> & vertices){
	init(4,vertices.size());
	for (int i = 0; i < vertices.size(); ++i){
		data[i*4 + 0] = vertices[i][0];
		data[i*4 + 1] = vertices[i][1];
		data[i*4 + 2] = vertices[i][2];
		data[i*4 + 3] = vertices[i][3];
	}
}

VertexAttributeArray::VertexAttributeArray(const std::vector<glm::vec3> & vertices){
	init(3,vertices.size());
	for (int i = 0; i < vertices.size(); ++i){
		data[i*3 + 0] = vertices[i][0];
		data[i*3 + 1] = vertices[i][1];
		data[i*3 + 2] = vertices[i][2];
	}
}

VertexAttributeArray::VertexAttributeArray(const std::vector<glm::vec2> & vertices){
	init(2,vertices.size());
	for (int i = 0; i < vertices.size(); ++i){
			data[i*2 + 0] = vertices[i][0];
			data[i*2 + 1] = vertices[i][1];
	}
}

void VertexAttributeArray::attach(int pos) const{
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos,size,GL_FLOAT,GL_FALSE,0,0);
}

}
