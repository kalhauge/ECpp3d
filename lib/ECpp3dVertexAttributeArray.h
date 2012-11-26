/*
 * ECpp3dVertexAttributeArray.h
 *
 *  Created on: 25/11/2012
 *      Author: christian
 */

#ifndef ECPP3DVERTEXATTRIBUTEARRAY_H_
#define ECPP3DVERTEXATTRIBUTEARRAY_H_

#include "ECpp3dUtils.h";
#include "ECpp3dBuffer.h"
#include <vector>
#include <glm/glm.hpp>
namespace ECpp3d{

class VertexAttributeArray : public ECpp3dMemoryObject {
protected:
	GLuint location;
	GLsizei vert_size;
	GLint number_of_vertices;
	ArrayBuffer buffer;
	static const VertexAttributeArray * bound;
	void ensureBound() const;
public:

	static std::vector<VertexAttributeArray> generateVertexArrays(GLsizei size);
	static VertexAttributeArray generateVertexArray();

	~VertexAttributeArray();
	VertexAttributeArray();
	VertexAttributeArray(const ArrayBuffer & buffer,GLuint location);

	void initialize(int vector_size,int size);
	void initialize(int vector_size,int size,const GLfloat * data);

	void finalize();
	void attach(int pos) const;
};

}




#endif /* ECPP3DVERTEXATTRIBUTEARRAY_H_ */
