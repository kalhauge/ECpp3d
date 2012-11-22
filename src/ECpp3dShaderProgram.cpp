//
//  ECpp3dShaderProgram.cpp
//  ecpp3d
//
//  Created by Christian Gram Kalhauge on 04/11/12.
//  Copyright (c) 2012 Kalhauge. All rights reserved.
//

#include "ECpp3dShaderProgram.h"

#include <string.h>

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

ShaderProgram * ShaderProgram::used = NULL;

void ShaderProgram::setVertexShaderCode(const char *vertex_shader_code){
    this->vertex_shader_length = (GLuint) strlen(vertex_shader_code);
    this->vertex_shader_code = getsafestrcopy(vertex_shader_code);
}

void ShaderProgram::setFragmentShaderCode(const char *fragment_shader_code){
    this->fragment_shader_length = (GLuint) strlen(fragment_shader_code);
    this->fragment_shader_code = getsafestrcopy(fragment_shader_code);
}

void ShaderProgram::ensureUsed() {
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

Uniform::Uniform(GLuint program_id,GLuint index) {
	char * buffer = new char[128];
	GLsizei length = 0;
	glGetActiveUniform(program_id,index,128,&length,&size,&type,buffer);
	this->index = index;
	name = std::string(buffer,length);
	delete[] buffer;
}
const std::string Uniform::toString() const {
	std::stringstream s;
	s << "<Uniform " << name << " at [" << index << "]>";
	return s.str();
}

Attribute::Attribute(GLuint program_id,GLuint index) {
	char * buffer = new char[128];
	GLsizei length = 0;
	glGetActiveAttrib(program_id,index,128,&length,&size,&type,buffer);
	name = std::string(buffer,length);
	this->index = index;
	delete[] buffer;

}

const std::string Attribute::toString() const {
	std::stringstream s;
	s << "<Attribute " << name << " at [" << index << "]>";
	return s.str();
}

}



