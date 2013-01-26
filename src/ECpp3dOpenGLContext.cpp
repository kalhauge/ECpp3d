/*
 * ECpp3dOpenGLContext.cpp
 *
 *  Created on: 03/12/2012
 *      Author: christian
 */

#include "ECpp3dOpenGLContext.h"
#include "handlers/ECpp3dFramebuffer.h"

namespace ECpp3d {

Framebuffer * const OpenGLContext::SCREEN = new Framebuffer(0);
bool OpenGLContext::initialized = false;
const Area * OpenGLContext::viewport = 0;

Samplers OpenGLContext::samplers = Samplers();
std::set<const Sampler*> OpenGLContext::freeSamplers = std::set<const Sampler*>();

ShaderVariableManager OpenGLContext::manager;

const UniformDescription & OpenGLContext::U(const std::string & name) 
throw (ShaderVariableDoesNotExistException) {
	return manager.getUniformDescription(name);
}

const UniformDescription & OpenGLContext::U(const Uniform & uniform)
throw (ShaderVariableDoesNotExistException) {
	return manager.getUniformDescription(uniform.getName());
}

const AttributeDescription & OpenGLContext::A(const std::string & name)
throw (ShaderVariableDoesNotExistException) {
	return manager.getAttributeDescription(name);
}

const OutputDescription & OpenGLContext::O(const std::string & name) 
throw (ShaderVariableDoesNotExistException) {
	return manager.getOutputDescription(name);
}

void OpenGLContext::load(const AttributeDescription & v)
throw (ShaderVariableDoesExistException) {
	manager.registerAttribute(v);
}

void OpenGLContext::load(const UniformDescription & v)
throw (ShaderVariableDoesExistException) {
	manager.registerUniform(v);
}
void OpenGLContext::load(const OutputDescription & v)
throw (ShaderVariableDoesExistException) {
	manager.registerOutput(v);
}

void OpenGLContext::loadStandardVariableDescription()
throw (ShaderVariableDoesExistException){
	manager.loadStandards();
}



const AttributeDescriptions & OpenGLContext::getAttributeDescriptions() {
	return manager.getAttributeDescriptions();
}
const UniformDescriptions & OpenGLContext::getUniformDescriptions() {
	return manager.getUniformDescriptions();
}
const OutputDescriptions & OpenGLContext::getOutputDescriptions() {
	return manager.getOutputDescriptions();
}

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


void OpenGLContext::setViewport(const Area * const viewport){
	if(OpenGLContext::viewport != viewport) {
		OpenGLContext::viewport = viewport;
		glViewport(viewport->x,viewport->y,viewport->width,viewport->height);
	}
}

void OpenGLContext::draw(const Framebuffer & buffer,const ShaderProgram & program,const VertexArray & object){
	buffer.makedrawable();
	program.use();
	object.bind();
}

void OpenGLContext::draw(const Framebuffer * buffer,const ShaderProgram * program,const VertexArray * object) {
	draw(*buffer,*program,*object);
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


