//
//  ECpp3dShaderProgram.cpp
//  ecpp3d
//
//  Created by Christian Gram Kalhauge on 04/11/12.
//  Copyright (c) 2012 Kalhauge. All rights reserved.
//

#include "ECpp3dShaderProgram.h"
#include <string.h>
#include <glm/gtc/type_ptr.hpp>


GLchar * getsafestrcopy(const char * code) {
    size_t length = strlen(code);
    char * copy = new char[length+1];
    copy[length] = 0;
    strcpy(copy,code);
    return copy;
}


namespace ECpp3d {

ShaderProgram::ShaderProgram(){
	program_id = -1;
	fragment_shader_code = NULL;
	vertex_shader_code = NULL;
	fragment_shader_length = 0;
	vertex_shader_length = 0;
	vertex_shader_id = -1;
	fragment_shader_id = -1;
}

ShaderProgram::ShaderProgram(const char * vertex_shader_code,const char * fragment_shader_code){
    ShaderProgram();
    setFragmentShaderCode(fragment_shader_code);
    setVertexShaderCode(vertex_shader_code);
}

GLboolean ShaderProgram::compile() throw (ShaderCompileException){
    GLint status;
    vertex_shader_id = compileShader(vertex_shader_code,vertex_shader_length,GL_VERTEX_SHADER);
    fragment_shader_id = compileShader(fragment_shader_code,fragment_shader_length,GL_FRAGMENT_SHADER);
    
    program_id = glCreateProgram();
    
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);

    glBindFragDataLocation(program_id,0,"fragColor");

    glLinkProgram(program_id);
    
    
    glGetProgramiv(program_id, GL_LINK_STATUS, &status);
    if(status != GL_TRUE){
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &status);
        const char * err_message;
        if(status > 0) {
            char * message = new char[status];
            message[status] = 0;
            GLint length;
            glGetProgramInfoLog(program_id, status, &length, message);
            err_message = message;
        } else {
            err_message = "No message in Shader Log";
        }
        glDeleteProgram(program_id);
        throw ShaderCompileException(err_message);
    }

    return status == GL_TRUE;

}

GLuint ShaderProgram::compileShader(const GLchar * code,const GLint length,const GLenum type) throw (ShaderCompileException) {
    GLint status;
    GLuint loc = glCreateShader(type);
    glShaderSource(loc,1,&code,&length);
    glCompileShader(loc);
    
    glGetShaderiv(loc, GL_COMPILE_STATUS, &status);
    
    if(status != GL_TRUE){
        glGetShaderiv(loc, GL_INFO_LOG_LENGTH, &status);
        const char * err_message;
        if(status > 0) {
            char * message = new char[status+1];
            message[status] = 0;
            GLint lenght;
            glGetShaderInfoLog(loc, status, &lenght, message);
            err_message = message;
        } else {
            err_message = "No message in Shader Log";
        }
        glDeleteShader(loc);
        throw ShaderCompileException(err_message);
    }
    
    return loc;
}

const ShaderProgram * ShaderProgram::used = NULL;

void ShaderProgram::setVertexShaderCode(const char *vertex_shader_code){
    this->vertex_shader_length = (GLuint) strlen(vertex_shader_code);
    this->vertex_shader_code = getsafestrcopy(vertex_shader_code);
}

void ShaderProgram::setFragmentShaderCode(const char *fragment_shader_code){
    this->fragment_shader_length = (GLuint) strlen(fragment_shader_code);
    this->fragment_shader_code = getsafestrcopy(fragment_shader_code);
}

void ShaderProgram::ensureUsed() const{
	if(used != this) {
		used = this;
		glUseProgram(program_id);
	}
}

std::vector<Uniform> ShaderProgram::getActiveUniformList() {
	GLint length = getNumberOfActiveUniforms();
	std::vector<Uniform> uniforms;

	for(int i = 0; i< length; i++){
		uniforms.push_back(Uniform(program_id,i));
	}
	return uniforms;
}

std::vector<Attribute> ShaderProgram::getActiveAttributeList() {
	GLint length = getNumberOfActiveAttributes();
	std::vector<Attribute> attributes;

	for(int i = 0; i< length; i++){
		attributes.push_back(Attribute(program_id,i));
	}
	return attributes;
}


void ShaderProgram::initialize(bool useStandarts) throw (ShaderCompileException){
	if(program_id == -1 || getServerInfo(GL_LINK_STATUS) != GL_TRUE) {
		throw ShaderCompileException("Can not initialize the program before it is compiled");
	}
	try{
		if(useStandarts) manager.loadStandards();
		manager.loadVariables(getActiveUniformList(),getActiveAttributeList());
	}catch(const ShaderVariableException & e) {
		throw ShaderCompileException(e.getMessage());
	}
}

void ShaderProgram::attachAttribute(const AttributeDescription & description, const VertexArray & array) const{
	ensureUsed();
	const Attribute a = manager.getAttribute(description);
	array.attach(a.getIndex());
}


template<>
void ShaderProgram::attachUniform<glm::mat4>(const UniformDescription & description, const glm::mat4 & a) const{
	ensureUsed();
	const Uniform u = manager.getUniform(description);
	assert(u.getType() == GL_FLOAT_MAT4);
	glUniformMatrix4fv(u.getIndex(),1,GL_FALSE,glm::value_ptr(a));
}

template<>
void ShaderProgram::attachUniform<glm::vec4>(const UniformDescription & description, const glm::vec4 & a) const{
	ensureUsed();
	const Uniform u = manager.getUniform(description);
	assert(u.getType() == GL_FLOAT_VEC4);
	glUniform4fv(u.getIndex(),1,glm::value_ptr(a));
}



}



