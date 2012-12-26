/*
 * ECpp3dOpenGLContext.cpp
 *
 *  Created on: 03/12/2012
 *      Author: christian
 */

#include "ECpp3dOpenGLContext.h"

namespace ECpp3d {

bool OpenGLContext::initialized = false;
Samplers OpenGLContext::samplers = Samplers();
std::set<const Sampler*> OpenGLContext::freeSamplers = std::set<const Sampler*>();

void OpenGLContext::printspecs(std::ostream & out) {
  out << "Vendor:   " << glGetString(GL_VENDOR) << std::endl;
  out << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
  out << "Version:  " << glGetString(GL_VERSION) << std::endl;
  out << "GLSL:     " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void OpenGLContext::checkForErrors() throw (OpenGLException) {
	GLenum error = glGetError();

	switch(error) {
	case GL_NO_ERROR:
		break;
	case GL_OUT_OF_MEMORY:
		throw OpenGLOutOfMemmoryException();
	case GL_INVALID_OPERATION:
		throw OpenGLInvalidOperationException();
	case GL_INVALID_ENUM:
			throw OpenGLInvalidEnumException();
	case GL_INVALID_VALUE:
			throw OpenGLInvalidValueException();
	default: throw OpenGLException();
	}
}

const Sampler * OpenGLContext::getSampler() {
	std::set<const Sampler*>::iterator first = freeSamplers.begin();
	freeSamplers.erase(first);
	return *first;
}
void OpenGLContext::initialize() {
	initialized = true;
	samplers = Sampler::getSamplers();
	resetSamplers();
}


GLuint OpenGLContext::getMaxCombinedTextureImageUnits(){
	return getInteger(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);
}

void OpenGLContext::resetSamplers() {
	freeSamplers.clear();
	std::copy(samplers.begin(),samplers.end(),std::inserter(freeSamplers,freeSamplers.begin()));
}

void OpenGLContext::free(const Sampler * sampler) {
	freeSamplers.insert(sampler);
}

GLsizei OpenGLContext::getSizeOf(GLenum e) {
	switch (e) {
	case GL_FLOAT 	: return 4;
	case GL_INT 	: return 4;
	case GL_BYTE 	: return 1;
	default			: return 0;
	}
}

}


