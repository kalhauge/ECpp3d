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

VertexAttributeArray::VertexAttributeArray(int vector_size, int vertices){
	data = new GLfloat[vector_size*vertices];
	size = vector_size;
	number_of_vertices = vertices;
}

VertexAttributeArray::VertexAttributeArray(const std::vector<glm::vec4> & vertices){
	VertexAttributeArray(4,vertices.size());
}

VertexAttributeArray::VertexAttributeArray(const std::vector<glm::vec3> & vertices){
	VertexAttributeArray(3,vertices.size());
}

VertexAttributeArray::VertexAttributeArray(const std::vector<glm::vec2> & vertices){
	VertexAttributeArray(2,vertices.size());
}

void VertexAttributeArray::put(int i,const glm::vec4 & data) {

}

}
