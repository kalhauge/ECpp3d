/*
 * ECpp3dUtils.h
 *
 *  Created on: 20/11/2012
 *      Author: christian
 */

#ifndef ECPP3DUTILS_H_
#define ECPP3DUTILS_H_


#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "ECpp3dOpenGL.h"

namespace ECpp3d {

class Object;
class OpenGLHandler;
class Exception;
class NotInitializedException;
class OpenGLException;
class OpenGLOutOfMemmoryException;
class OpenGLInvalidOperationException;
class OpenGLInconsistentStateException;

class Object {
	virtual const std::string toString() const {
		std::stringstream s;
		s << "<Object at:" << this << ">";
		return s.str();
	}

	friend std::ostream& operator<< (std::ostream& stream, const Object& object) {
		return stream << object.toString();
	}
};

class Exception : public Object {
	std::string message;
public:
    ~Exception() {}

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


class OpenGLHandler : public Object {
public:
	virtual void finalize() = 0;
	virtual void validate() const throw (OpenGLException)= 0;
};


void printspecs(std::ostream & out);


}



#endif /* ECPP3DUTILS_H_ */
