/*
 * ECpp3dVertexArray.h
 *
 *  Created on: 25/11/2012
 *      Author: christian
 */

#ifndef ECPP3DVERTEXARRAY_H_
#define ECPP3DVERTEXARRAY_H_

#include "ECpp3dUtils.h";
#include "handlers/ECpp3dBuffer.h"
#include <vector>
#include <glm/glm.hpp>
namespace ECpp3d{

class VertexArray;

typedef std::vector<VertexArray*> VertexArrays;

class VertexArray : public OpenGLHandler {
protected:
	GLsizei vert_size;
	GLint number_of_vertices;
	ArrayBuffer & buffer;
	static const VertexArray * bound;
	void ensureBound() const;
public:

	static VertexArrays generateVertexArrays(GLsizei size);
	static VertexArray * generateVertexArray();

	virtual ~VertexArray();
	VertexArray(ArrayBuffer * const buffer,GLuint location)
		: OpenGLHandler(location), buffer(*buffer) {
		vert_size = 0;
		number_of_vertices = 0;
	}

	void initialize(int vector_size,int size);
	void initialize(int vector_size,int size,const GLfloat * data);

	void finalize();
	void validate() const throw (OpenGLException);
	void attach(int pos) const;
};

}




#endif /* ECPP3DVERTEXARRAY_H_ */
