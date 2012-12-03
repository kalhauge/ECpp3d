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

typedef std::vector<Object*> Objects;

class Object {
public:

	virtual ~Object() {};

	virtual const std::string toString() const {
		std::stringstream s;
		s << "<Object at:" << this << ">";
		return s.str();
	}

	friend std::ostream& operator<< (std::ostream& stream, const Object& object) {
		return stream << object.toString();
	}

	static void deleteObjects(Objects * const object);
};

inline std::ostream& operator<<(std::ostream& stream,Objects & object) {
	return stream << "<ObjectVector : "<< object.size() <<">";
}
}


#include "ECpp3dException.h"

namespace ECpp3d {

class OpenGLHandler;
typedef std::vector<OpenGLHandler*> Handlers;


class OpenGLHandler : public Object {
protected:
	const GLuint location;
	OpenGLHandler(GLuint location) : location(location) {};
public:
	virtual ~OpenGLHandler() {};
	virtual void finalize() = 0;
	virtual void validate() const throw (OpenGLException)= 0;

	static void finalize(Handlers * const handlers);

	GLuint getLocation() const {return location;}
};


#include "ECpp3dOpenGLContext.h"

}

#endif /* ECPP3DUTILS_H_ */
