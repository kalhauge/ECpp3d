/*
 * ECpp3dFramebuffer.cpp
 *
 *  Created on: 16/12/2012
 *      Author: christian
 */

#include "handlers/ECpp3dFramebuffer.h"
#include "ECpp3dOpenGLContext.h"

namespace ECpp3d {

const Framebuffer * Framebuffer::bound = OpenGLContext::SCREEN;

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

void Framebuffer::attach(int i,const Texture2D * const texture){
	bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0 + i,GL_TEXTURE_2D,texture->getLocation(),0);
}

void Framebuffer::validate() const throw (OpenGLException) {
	bind();
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		throw OpenGLException();
}

void Framebuffer::clearColor(const glm::vec4 &color){
	bind();
	glClearColor(color.r,color.g,color.b,color.a);
	glClear(GL_COLOR_BUFFER_BIT);
}
void Framebuffer::makedrawable() const {
	bind();
	OpenGLContext::setViewport(viewport);
}

void Framebuffer::setViewport(const Area * const area) {
	viewport = area;
}
}

