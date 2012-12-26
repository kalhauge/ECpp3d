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
#include "ECpp3dShaderVariable.h"
#include "ECpp3dShaderProgram.h"
#include <vector>
#include <glm/glm.hpp>
namespace ECpp3d{

class VertexArray;

typedef std::vector<VertexArray*> VertexArrays;

class VertexArray : public OpenGLHandler {
protected:

	typedef std::pair<const AttributeDescription *,const ArrayBuffer*> VertexArrayData;

	GLint numberOfVerts;
	std::vector<VertexArrayData > buffers;
	static const VertexArray * bound;
	void bind(bool force = false) const;
	static void unbind();
public:

	static VertexArrays generateVertexArrays(GLsizei size);
	static VertexArray * generateVertexArray();

	virtual ~VertexArray();
	VertexArray(GLuint location)
		: OpenGLHandler(location){
		numberOfVerts = 0;
	}

	void add(const AttributeDescription & desc,const ArrayBuffer * buffer);
	void initialize(GLsizei numberOfVerts);

	void finalize();
	void validate() const throw (OpenGLException);
	void attachTo(ShaderProgram & program) const;
	const std::string toString() const;
};

}




#endif /* ECPP3DVERTEXARRAY_H_ */
