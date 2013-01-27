//
// ECpp3d.cpp


#include "ECpp3dUtils.h"
#include <sstream>

namespace ECpp3d {


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

const std::string OpenGLInvalidEnumException::getMessage() const {
	return "<OpenGLInvalidEnumException>";
}

const std::string OpenGLInvalidValueException::getMessage() const {
	return "<OpenGLInvalidValueException>";
}

void OpenGLHandler::finalize(Handlers * const handlers) {
	for(unsigned int i = 0; i < handlers->size(); ++i) {
		(*handlers)[i]->finalize();
	}
	deleteObjects((Objects*)handlers);
}

void Object::deleteObjects(Objects * const objects) {
	for(unsigned int i = 0; i < (*objects).size(); ++i) {
		delete (*objects)[i];
	}
}

Area Area::STDSIZE = Area(0,0,256,256);
Area::Area(GLsizei x, GLsizei y , GLsizei width, GLsizei height) : x(x), y(y) ,width(width), height(height) {}

/* 
name: (type:GLenum) -> getTypeSize -> (size in bytes of type:int)
returns -1 if the type is not found
*/

int typeSize(GLenum type) {
    switch (type) {
        case GL_UNSIGNED_BYTE   : return 1;
        case GL_BYTE            : return 1;
        
        case GL_UNSIGNED_SHORT  : return 2;
        case GL_SHORT           : return 2;
        
        case GL_UNSIGNED_INT    : return 4;
        case GL_INT             : return 4;
        
        case GL_FLOAT           : return 4;
        case GL_DOUBLE          : return 8;
        default        : return -1;
    }
}

/* 
name: (fromat:GLenum) -> getTypeSize -> (number of fields used in format:int)
returns -1 if the format is not known;
*/

int formatSize(GLenum format) {
    switch (format) {
        case GL_RGBA    : return 4;
        case GL_RGB     : return 3;
        case GL_RG      : return 2;
        case GL_R8      : return 1;
        default         : return -1;
    }
}

GLenum getType(GLfloat type) {return GL_FLOAT;};
GLenum getType(GLubyte type) {return GL_UNSIGNED_BYTE;};
GLenum getType(GLbyte type) {return GL_BYTE;};
GLenum getType(GLshort type) {return GL_SHORT;};
GLenum getType(GLint type) {return GL_INT;};
GLenum getType(GLuint type) {return GL_UNSIGNED_INT;};

}

