/*
 * ECpp3dFramebuffer.cpp
 *
 *  Created on: 16/12/2012
 *      Author: christian
 */

#include "handlers/ECpp3dFramebuffer.h"


namespace ECpp3d {

const Framebuffer * const Framebuffer::SCREEN = new Framebuffer(0);
const Framebuffer * Framebuffer::bound = Framebuffer::SCREEN;

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

void Framebuffer::bind(bool force) const {
	if(bound != this || force) {
		bound = this;
		glBindFramebuffer(GL_FRAMEBUFFER,location);
	}
}

void Framebuffer::attach(int i,const Texture2D & texture){
	bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0 + i,GL_TEXTURE_2D,texture.getLocation(),0);
}

void Framebuffer::validate() const throw (OpenGLException) {
	bind();
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		throw OpenGLException();
}

}

