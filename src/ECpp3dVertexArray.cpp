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
	VertexArrays arrays;
	for(int i = 0; i < size; ++i) {
		VertexArray * narray = new VertexArray(locations[i]);
		arrays.push_back(narray);
	}
	return arrays;
}

VertexArray * VertexArray::generateVertexArray() {
	return generateVertexArrays(1)[0];
}

VertexArray::~VertexArray() {

}

const std::string VertexArray::toString() const {
	std::stringstream s;
	s << "<VertexArray at [" << location << "] - dim: " << numberOfVerts <<  " buffers: " << buffers.size() << ">";
	return s.str();
}


void VertexArray::bind(bool force) const{
	if(bound != this || force) {
		bound = this;
		glBindVertexArray(location);
	}
}

void VertexArray::unbind(){
	bound = 0;
	glBindVertexArray(0);
}

void VertexArray::add(const AttributeDescription & desc,const ArrayBuffer * buffer) {
	VertexArrayData data = VertexArrayData(&desc,buffer);
	buffers.push_back(data);
}


void VertexArray::initialize(GLsizei numberOfVerts){
	bind();
	this->numberOfVerts = numberOfVerts;
}

void VertexArray::finalize() {
	glDeleteVertexArrays(1,&location);
}

void VertexArray::validate() const throw (OpenGLException){
	for(int i =0; i < buffers.size(); i++ ) {
		buffers[i].second->validate();
	}
}

void VertexArray::attachTo(ShaderProgram & program) const{
	bind();
	for(int i = 0; i < buffers.size(); i++)
		program.attachAttribute(*(buffers[i].first),*(buffers[i].second));
}

}
