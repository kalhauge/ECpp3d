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

void OpenGLHandler::finalize(Handlers * const handlers) {
	for(int i = 0; i < handlers->size(); ++i) {
		(*handlers)[i]->finalize();
	}
	deleteObjects((Objects*)handlers);
}

void Object::deleteObjects(Objects * const objects) {
	for(int i = 0; i < (*objects).size(); ++i) {
		delete (*objects)[i];
	}
}

}

