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
	GLsizeiptr size;
	GLenum usage;
	void setData(GLenum target, GLintptr at, const GLvoid * data, GLsizei size);

	Buffer(GLuint location) : OpenGLHandler(location) {
		this->size = 0;
		this->usage = 0;
	}
public:
	static Buffers generateBuffers(GLsizei number);
	static Buffer * generateBuffer();

	virtual void initialize(GLenum target, const GLvoid * data,GLsizeiptr size, GLenum usage);
	virtual void finalize();
	virtual void validate() const throw (OpenGLException) {};

	virtual const std::string toString() const;
	GLint getServerInfo(GLenum target,GLenum e) const;
};

class ArrayBuffer : public Buffer {
	static const GLuint target = GL_ARRAY_BUFFER;
	static const ArrayBuffer * bound;
	void ensureBound() const;
public:
	ArrayBuffer(const Buffer * buffer) : Buffer(buffer->getLocation()) {
		delete buffer;
	};
	void initialize(const GLvoid * data,GLsizeiptr size,GLenum hint);
	void setData(GLintptr at, const GLvoid * data, GLsizei size);
	void validate() const throw (OpenGLException);
	void bind() const;

	GLint getServerInfo(GLenum e) const;
};

}



#endif /* ECPP3DBUFFER_H_ */
