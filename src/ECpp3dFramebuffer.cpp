/*
 * ECpp3dFramebuffer.cpp
 *
 *  Created on: 16/12/2012
 *      Author: christian
 */

#include "handlers/ECpp3dFramebuffer.h"


namespace ECpp3d {

const Framebuffer * const Framebuffer::SCREEN = new Framebuffer(0);

Framebuffers Framebuffer::generateFramebuffers(GLsizei number){
	GLuint locations[number];
	glGenFramebuffers(number,locations);

	Framebuffers buffers;

	for(int i = 0; i < number; ++i) {
		Framebuffer * nbuffer = new Framebuffer(locations[i]);
		buffers.push_back(nbuffer);
	}

	return buffers;
}

Framebuffer * Framebuffer::generateFramebuffer(){
	return generateFramebuffers(1)[0];
}

void Framebuffer::attach(std::string name,Texture * texture){

}

void Framebuffer::validate() const throw (OpenGLException) {

}

}

