/*
 * ECpp3dException.h
 *
 *  Created on: 01/12/2012
 *      Author: christian
 */

#ifndef ECPP3DEXCEPTION_H_
#define ECPP3DEXCEPTION_H_


namespace ECpp3d {

class Object;
class OpenGLHandler;


class Exception : public Object {
	std::string message;
public:
    virtual ~Exception() {}

    virtual void setMessage(const std::string & message){
    	this->message = std::string(message);
    }

    virtual const std::string getMessage() const {return message;}
    const std::string toString() const {return getMessage();}
};

class NotInitializedException : public Exception {
	const Object * object;
public:
	NotInitializedException(const Object * object);
	void setObject(const Object * object);
	const std::string getMessage() const;
};


class OpenGLException : public Exception {};

class OpenGLOutOfMemmoryException : public OpenGLException {
public:	const std::string getMessage() const;
};

class OpenGLInvalidOperationException : public OpenGLException {
public: const std::string getMessage() const;
};

class OpenGLInvalidEnumException :public OpenGLException {
public: const std::string getMessage() const;
};

class OpenGLInconsistentStateException : public OpenGLException {
	const OpenGLHandler * handler;
	std::string name;
	GLint handler_value;
	GLint server_value;
public:
	OpenGLInconsistentStateException(
			const OpenGLHandler * handler,
			const std::string & name,
			GLint handler,
			GLint server);
	const std::string getMessage() const;
};



}

#endif /* ECPP3DEXCEPTION_H_ */
