//
//  ECpp3dShaderProgram.cpp
//  ecpp3d
//
//  Created by Christian Gram Kalhauge on 04/11/12.
//  Copyright (c) 2012 Kalhauge. All rights reserved.
//

#include "ECpp3dShaderProgram.h"
#include "handlers/ECpp3dTexture.h"
#include "ECpp3dOpenGLContext.h"
#include <string>
#include <fstream>
#include <iterator>
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

GLboolean ShaderProgram::compile(bool useStandarts) throw (ShaderCompileException){

    GLint status;
    vertex_shader_id = compileShader(vertex_shader_code,vertex_shader_length,GL_VERTEX_SHADER);
    fragment_shader_id = compileShader(fragment_shader_code,fragment_shader_length,GL_FRAGMENT_SHADER);
    
    program_id = glCreateProgram();
    
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);

    OutputDescriptions o = OpenGLContext::getOutputDescriptions();

    for(OutputDescriptions::iterator i = o.begin(); i != o.end(); ++i){
    	glBindFragDataLocation(program_id,(*i)->getId(),(*i)->getName().c_str());
     }

    AttributeDescriptions a = OpenGLContext::getAttributeDescriptions();

    for(AttributeDescriptions::iterator i = a.begin(); i != a.end(); ++i){
    	glBindAttribLocation(program_id,(*i)->getId(),(*i)->getName().c_str());
    }

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
        std::string err_message;
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
        throw ShaderCompileException((type == GL_FRAGMENT_SHADER ? "Fragment Shader: " : "Vertex Shader: ") + err_message);
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

void ShaderProgram::use(bool force) const{
	if(used != this || force) {
		used = this;
		glUseProgram(program_id);
	}
}


void ShaderProgram::addUniform(const Uniform & uniform) throw (ShaderVariableDoesNotExistException){
	UniformDescription a = OpenGLContext::U(uniform);
	uniforms[a.getId()] = new Uniform(uniform);
}

void ShaderProgram::loadUniforms() throw (ShaderVariableDoesNotExistException){
	std::vector<Uniform> u = getActiveUniformList();
	for(std::vector<Uniform>::iterator i = u.begin(); i != u.end(); ++i) {
		addUniform(*i);
	}
}

/* OBS
 * Returns 0 if not found
 */
const Uniform * ShaderProgram::getUniform(const UniformDescription & desc) const {
	std::map<int,Uniform*>::const_iterator i = uniforms.find(desc.getId());
	if(i != uniforms.end()) {
		return i->second;
	} else return 0;
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

std::string getFileContent(const std::string & filename) throw (IOException) {
	std::ifstream file(filename.c_str());
	if(file) {
		std::string a;
		file.seekg(0,std::ios::end);
		a.resize(file.tellg());
		file.seekg(0,std::ios::beg);
		file.read(&a[0],a.size());
		return a;
	} else throw IOException("No file found: " + filename);

}

ShaderProgram * ShaderProgram::fromPath(const std::string & program_loc) throw (ShaderCompileException,IOException) {
	return fromPath(program_loc + ".vs", program_loc + ".fs");
}


ShaderProgram * ShaderProgram::fromPath(
		const std::string &  vert_shader_loc,
		const std::string & frag_shader_loc) throw (ShaderCompileException,IOException){
	ShaderProgram & p = *(new ShaderProgram());
	p.setVertexShaderCode(getFileContent(vert_shader_loc).c_str());
	p.setFragmentShaderCode(getFileContent(frag_shader_loc).c_str());
	p.compile();
	return &p;
}

void ShaderProgram::initialize() throw (ShaderCompileException){
	if(program_id == -1 || getServerInfo(GL_LINK_STATUS) != GL_TRUE) {
		throw ShaderCompileException("Can not initialize the program before it is compiled");
	}
	try{
		loadUniforms();
	}catch(const ShaderVariableException & e) {
		throw ShaderCompileException(e.getMessage());
	}
}

GLuint ShaderProgram::getProgramId() const{
	return program_id;
}

void ShaderProgram::validate() throw (OpenGLException) {
	glValidateProgram(program_id);
	if(!getServerInfo(GL_VALIDATE_STATUS)) {
		char a[1024];
		int length;
		glGetProgramInfoLog(program_id,1024,&length,a);
		OpenGLException e;
		e.setMessage(a);
		throw e;
	}
}


void ShaderProgram::attachUniform(const UniformDescription & description, const glm::mat4 & a) const{
	use();
	const Uniform * u = getUniform(description);
	if(!u) return;
	assert(u->getType() == GL_FLOAT_MAT4);
	glUniformMatrix4fv(u->getIndex(),1,GL_FALSE,glm::value_ptr(a));
}

void ShaderProgram::attachUniform(const UniformDescription & description, const glm::vec4 & a) const{
	use();
	const Uniform * u = getUniform(description);
	if(!u) return;
	assert(u->getType() == GL_FLOAT_VEC4);
	glUniform4fv(u->getIndex(),1,glm::value_ptr(a));
}

void ShaderProgram::attachUniform(const UniformDescription & description, const GLint & a) const{
	use();
	const Uniform * u = getUniform(description);
	if(!u) return;
	assert(u->getType() == GL_INT);
	glUniform1i(u->getIndex(),a);
}

void ShaderProgram::attachUniform(const UniformDescription & description, Texture * t) const{
	use();
	const Uniform * u = getUniform(description);
	if(!u) return;
	t->attach(*u);
}


void ShaderProgram::printActiveVariables(std::ostream & o) {
    o << "Uniforms [";
    std::vector<Uniform> uniforms = this->getActiveUniformList();
    std::copy(uniforms.begin(),uniforms.end(),std::ostream_iterator<Uniform>(o, ", "));
    o << "]" << std::endl;

    o << "Attributes [";
    std::vector<Attribute> attributes = this->getActiveAttributeList();
    std::copy(attributes.begin(),attributes.end(),std::ostream_iterator<Attribute>(o, ", "));
    o << "]" << std::endl;

}

}



