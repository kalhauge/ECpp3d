//
// ECpp3d.cpp


#include "ECpp3dUtils.h"
#include <sstream>

namespace ECpp3d {

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
	default: throw OpenGLException();
	}
}

typedef std::vector<Object> objects;


NotInitializedException::NotInitializedException(
		const Object * object
		) {
	setObject(object);
}

void NotInitializedException::setObject(const Object * object) {
	this->object = object;
}

const std::string NotInitializedException::getMessage() const {
	std::stringstream s;
	s << "<NotInitializedException on: " << *object << ">";
	return s.str();
}

const std::string OpenGLOutOfMemmoryException::getMessage() const {
	return "<OpenGLOutOfMemmoryException>";
}
const std::string OpenGLInvalidOperationException::getMessage() const {
	return "<OpenGLInvalidOperationException>";
}
OpenGLInconsistentStateException::OpenGLInconsistentStateException(
		const OpenGLHandler * handler,
		const std::string & name,
		GLint handler_value,
		GLint server_value) {
	this->name = name;
	this->handler = handler;
	this->handler_value = handler_value;
	this->server_value = server_value;
}

const std::string OpenGLInconsistentStateException::getMessage() const {
	std::stringstream s;
	s << "<OpenGLInconsistentStateException on: "
			<< *handler
			<< " name: " << name
			<< " handler:" << handler_value
			<< " server:" << server_value
			<< ">";
	return s.str();
}

}

