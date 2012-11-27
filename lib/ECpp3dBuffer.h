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

class Buffer : public OpenGLHandler {
protected:
	GLuint location;
	GLsizei size;
	GLenum usage;
	void setData(GLenum target, GLintptr at, const GLvoid * data, GLsizei size);
public:
	static std::vector<Buffer> generateBuffers(GLsizei number);
	static Buffer generateBuffer();

	Buffer();
	Buffer(GLuint location);

	void initialize(GLenum target, const GLvoid * data,GLsizei size, GLenum usage);
	void finalize();
	void validate() const throw (OpenGLException);

	GLint getServerInfo(GLenum e) const;

	GLuint getLocation() const {return location;}
};

class ArrayBuffer : public Buffer {
	static const ArrayBuffer * bound;
public:
	ArrayBuffer();
	ArrayBuffer(const Buffer & buffer);
	void ensureBound() const;
	void initialize(const GLvoid * data,GLsizei size,GLenum hint);
	void setData(GLintptr at, const GLvoid * data, GLsizei size);
};

}



#endif /* ECPP3DBUFFER_H_ */
