/*
 * ECpp3dVertexArray.h
 *
 *  Created on: 25/11/2012
 *      Author: christian
 */

#ifndef ECPP3DVERTEXARRAY_H_
#define ECPP3DVERTEXARRAY_H_

#include "ECpp3dUtils.h";
#include "ECpp3dBuffer.h"
#include <vector>
#include <glm/glm.hpp>
namespace ECpp3d{

class VertexArray : public OpenGLHandler {
protected:
	GLuint location;
	GLsizei vert_size;
	GLint number_of_vertices;
	ArrayBuffer buffer;
	static GLuint bound;
	void ensureBound() const;
public:

	static std::vector<VertexArray> generateVertexArrays(GLsizei size);
	static VertexArray generateVertexArray();

	~VertexArray();
	VertexArray();
	VertexArray(const ArrayBuffer & buffer,GLuint location);

	void initialize(int vector_size,int size);
	void initialize(int vector_size,int size,const GLfloat * data);

	void finalize();
	void validate() const throw (OpenGLException);
	void attach(int pos) const;
};

}




#endif /* ECPP3DVERTEXARRAY_H_ */
