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
#include "handlers/ECpp3dBuffer.h"
#include "handlers/ECpp3dTexture.h"
#include <vector>
#include <string>

namespace ECpp3d {

class ShaderCompileException : public Exception {
public:
	ShaderCompileException(const std::string & message){setMessage(message);}
	~ShaderCompileException() {};
};


class ShaderProgram : public Object {
	GLuint vertex_shader_id, fragment_shader_id;
	GLchar * vertex_shader_code, * fragment_shader_code;
	GLuint vertex_shader_length, fragment_shader_length;

	GLuint program_id;

	std::map<int,Uniform*> uniforms;
	void addUniform(const Uniform & uniform) throw (ShaderVariableDoesNotExistException);
	void loadUniforms() throw (ShaderVariableDoesNotExistException);
	const Uniform * getUniform(const UniformDescription & desc) const;

	static GLuint compileShader(const char *  code,GLint length,GLenum type) throw (ShaderCompileException);
	const static ShaderProgram * used;


public:
	ShaderProgram();
	ShaderProgram(const char * vertex_shader_code, const char * fragment_shader_code);

	static ShaderProgram * fromPath(const std::string & program_loc)
			throw (ShaderCompileException,IOException);
	static ShaderProgram * fromPath(
			const std::string &  vert_shader_loc,
			const std::string & frag_shader_loc) throw (ShaderCompileException,IOException);

	ShaderProgram *  setVertexShaderCode(const char * vertex_sharder_code);
	ShaderProgram *  setFragmentShaderCode(const char * fragment_shader_code);
	std::vector<Uniform> getActiveUniformList();
	std::vector<Attribute> getActiveAttributeList();

	GLuint getProgramId() const;

	GLint getServerInfo(GLenum e) const;
	GLint getNumberOfActiveUniforms() const;
	GLint getNumberOfActiveAttributes() const;

	ShaderProgram *  initialize() throw (ShaderCompileException);
	ShaderProgram *  validate() throw (OpenGLException);

	ShaderProgram *  printActiveVariables(std::ostream & o);

	const ShaderProgram *  attachUniform(const UniformDescription & description, const glm::vec4 & a) const;
	const ShaderProgram *  attachUniform(const UniformDescription & description, const glm::mat4 & a) const;
	const ShaderProgram *  attachUniform(const UniformDescription & description, const glm::mat2 & a) const;
	const ShaderProgram *  attachUniform(const UniformDescription & description, const GLint & a) const;
	const ShaderProgram *  attachUniform(const UniformDescription & description, const GLfloat & a) const;
	const ShaderProgram *  attachUniform(const UniformDescription & description, Texture * a) const;

	void use(bool force = false) const;

	GLboolean compile(bool useStandards = true) throw (ShaderCompileException);
};

inline GLint ShaderProgram::getServerInfo(GLenum e) const{
	GLint result;
	glGetProgramiv(program_id,e,&result);
	return result;
}

inline GLint ShaderProgram::getNumberOfActiveUniforms() const{
	return getServerInfo(GL_ACTIVE_UNIFORMS);
}

inline GLint ShaderProgram::getNumberOfActiveAttributes() const{
	return getServerInfo(GL_ACTIVE_ATTRIBUTES);
}

}
#endif
