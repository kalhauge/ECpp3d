/*
 * ECpp3dOpenGLContext.cpp
 *
 *  Created on: 03/12/2012
 *      Author: christian
 */


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
	case GL_INVALID_ENUM:
			throw OpenGLInvalidEnumException();
	default: throw OpenGLException();
	}
}
}
