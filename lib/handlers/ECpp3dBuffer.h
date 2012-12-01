/*
 * ECpp3dBuffer.h
 *
 *  Created on: 26/11/2012
 *      Author: christian
 */

#ifndef ECPP3DBUFFER_H_
#define ECPP3DBUFFER_H_

#include "ECpp3dUtils.h"
#include <vector>

namespace ECpp3d {
class Buffer;
class ArrayBuffer;

typedef std::vector<Buffer*> Buffers;
typedef std::vector<ArrayBuffer*> ArrayBuffers;

class Buffer : public OpenGLHandler {
protected:
	const GLuint location;
	GLsizeiptr size;
	GLenum usage;
	void setData(GLenum target, GLintptr at, const GLvoid * data, GLsizei size);
public:
	static Buffers generateBuffers(GLsizei number);
	static Buffer * generateBuffer();


	Buffer(GLuint location) : location(location) {
		this->size = 0;
		this->usage = 0;
	}

	virtual void initialize(GLenum target, const GLvoid * data,GLsizeiptr size, GLenum usage);
	virtual void finalize();
	virtual void validate() const throw (OpenGLException) {};

	virtual const std::string toString() const;
	GLint getServerInfo(GLenum target,GLenum e) const;

	GLuint getLocation() const {return location;}
};

class ArrayBuffer : public Buffer {
	static const ArrayBuffer * bound;
	void ensureBound() const;
public:
	ArrayBuffer(const Buffer * buffer) : Buffer(buffer->getLocation()) {};
	void initialize(const GLvoid * data,GLsizeiptr size,GLenum hint);
	void setData(GLintptr at, const GLvoid * data, GLsizei size);
	virtual void validate() const throw (OpenGLException);
	GLint getServerInfo(GLenum e) const;
};

}



#endif /* ECPP3DBUFFER_H_ */
