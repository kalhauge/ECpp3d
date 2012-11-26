/*
 * ECpp3dVertexAttributeArray.h
 *
 *  Created on: 25/11/2012
 *      Author: christian
 */

#ifndef ECPP3DVERTEXATTRIBUTEARRAY_H_
#define ECPP3DVERTEXATTRIBUTEARRAY_H_

#include "ECpp3dUtils.h";
#include <vector>
#include <glm/glm.hpp>
namespace ECpp3d{

class VertexAttributeArray : public ECpp3dObject {
protected:
	GLint size;
	GLint number_of_vertices;
	GLfloat * data;

	void init(int vector_size,int size);

public:
	~VertexAttributeArray();
	VertexAttributeArray(const std::vector<glm::vec4> & vertices);
	VertexAttributeArray(const std::vector<glm::vec3> & vertices);
	VertexAttributeArray(const std::vector<glm::vec2> & vertices);
	VertexAttributeArray(const std::vector<GLfloat> & vertices);

	void setup();
	void attach(int pos) const;
};

}




#endif /* ECPP3DVERTEXATTRIBUTEARRAY_H_ */
