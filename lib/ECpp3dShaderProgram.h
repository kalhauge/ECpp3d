//
//  ECpp3dShaderProgram.h
//  ecpp3d
//
//  Created by Christian Gram Kalhauge on 04/11/12.
//  Copyright (c) 2012 Kalhauge. All rights reserved.
//

#ifndef ecpp3d_ECpp3dShaderProgram_h
#define ecpp3d_ECpp3dShaderProgram_h

#include "ECpp3dUtils.h"
#include "ECpp3dShaderVariable.h"
#include "ECpp3dVertexAttributeArray.h"
#include <vector>
#include <string>

namespace ECpp3d {

class ShaderCompileException : public ECpp3dException {
public:
	ShaderCompileException(const std::string & message){setMessage(message);}
	~ShaderCompileException() {};
};


class ShaderProgram : public ECpp3dObject {
	ShaderVariableManager manager;

	GLuint vertex_shader_id, fragment_shader_id;
	GLchar * vertex_shader_code, * fragment_shader_code;
	GLuint vertex_shader_length, fragment_shader_length;

	GLuint program_id;

	static GLuint compileShader(const char *  code,GLint length,GLenum type) throw (ShaderCompileException);
	const static ShaderProgram * used;


public:
	ShaderProgram();
	ShaderProgram(const char * vertex_shader_code, const char * fragment_shader_code);

	void setVertexShaderCode(const char * vertex_sharder_code);
	void setFragmentShaderCode(const char * fragment_shader_code);
	std::vector<Uniform> getActiveUniformList();
	std::vector<Attribute> getActiveAttributeList();

	GLint getProgramInfo(GLenum e) const;
	GLint getNumberOfActiveUniforms() const;
	GLint getNumberOfActiveAttributes() const;

	ShaderVariableManager & getVariableManager() {return manager;};

	void initialize(bool useStandards = true) throw (ShaderCompileException);

	template<typename type>
	void attachUniform(const UniformDescription & description, const type & a) const;

	void attachAttribute(const AttributeDescription & description, const VertexAttributeArray & array) const;

	void ensureUsed() const;

	GLboolean compile() throw (ShaderCompileException);
};

inline GLint ShaderProgram::getProgramInfo(GLenum e) const{
	GLint result;
	glGetProgramiv(program_id,e,&result);
	return result;
}

inline GLint ShaderProgram::getNumberOfActiveUniforms() const{
	return getProgramInfo(GL_ACTIVE_UNIFORMS);
}

inline GLint ShaderProgram::getNumberOfActiveAttributes() const{
	return getProgramInfo(GL_ACTIVE_ATTRIBUTES);
}

}
#endif