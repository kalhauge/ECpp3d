/*
 * ECpp3dShaderVariable.cpp
 *
 *  Created on: 24/11/2012
 *      Author: christian
 */

#include "ECpp3dShaderVariable.h"
#include <sstream>
namespace ECpp3d {


Uniform::Uniform(const Uniform & uniform) {
	index = uniform.index;
	size = uniform.size;
	type = uniform.type;
	name = uniform.name;
}

Uniform::Uniform(GLuint program_id,GLuint index) {
	char * buffer = new char[128];
	GLsizei length = 0;
	glGetActiveUniform(program_id,index,128,&length,&size,&type,buffer);
	name = std::string(buffer,length);
	this->index = glGetUniformLocation(program_id,name.c_str());
	delete[] buffer;
}
const std::string Uniform::toString() const {
	std::stringstream s;
	s << "<Uniform " << name << " at [" << index << "] of type 0x" << std::hex << type << ">";
	return s.str();
}

Attribute::Attribute(GLuint program_id,GLuint index) {
	char * buffer = new char[128];
	GLsizei length = 0;
	glGetActiveAttrib(program_id,index,128,&length,&size,&type,buffer);
	name = std::string(buffer,length);
	this->index = glGetAttribLocation(program_id,name.c_str());
	delete[] buffer;

}

ShaderVariableDoesExistException::ShaderVariableDoesExistException(const VariableDescription & n, const VariableDescription & o){
	std::stringstream s;
	s << "<ShaderVariableDoesNotExistException tried with : " << n << " already there : " <<  o << " >";
	setMessage(s.str());
}

ShaderVariableDoesNotExistException::ShaderVariableDoesNotExistException(const std::string & name) {
	std::stringstream s;
	s << "<ShaderVariableDoesNotExistException tried with : '" << name << "'>";
	setMessage(s.str());
}

const std::string Attribute::toString() const {
	std::stringstream s;
	s << "<Attribute " << name << " at [" << index << "]>";
	return s.str();
}
template<typename T>
void registerVariable(std::map<const std::string,const T> & map, std::vector<const T*> & referece, const T & desc) throw (ShaderVariableDoesExistException){
	typename std::map<const std::string,const T>::iterator i = map.find(desc.getName());
	if(i != map.end()) throw ShaderVariableDoesExistException(desc,i->second);
	map.insert(std::pair<std::string,T>(desc.getName(),desc));
	referece.push_back(&map.at(desc.getName()));
}

void ShaderVariableManager::registerUniform(const UniformDescription & desc) throw (ShaderVariableDoesExistException){
	registerVariable(uniform_ids,uniforms,desc);
}

void ShaderVariableManager::registerAttribute(const AttributeDescription & desc) throw (ShaderVariableDoesExistException){
	registerVariable(attribute_ids,attributes,desc);
}

void ShaderVariableManager::registerOutput(const OutputDescription & desc) throw (ShaderVariableDoesExistException){
	registerVariable(output_ids,outputs,desc);
}

void ShaderVariableManager::loadStandards() throw (ShaderVariableDoesExistException){
	registerUniform(UniformDescription::MVP_MATRIX);
	registerUniform(UniformDescription::MV_MATRIX);
	registerUniform(UniformDescription::COLOR);
	registerUniform(UniformDescription::COLOR_TEXTURE);
	registerAttribute(AttributeDescription::POSITION);
	registerAttribute(AttributeDescription::COLOR);
	registerAttribute(AttributeDescription::NORMAL);
	registerAttribute(AttributeDescription::TEXTURE_COORD_1);
	registerOutput(OutputDescription::STDOUT);

}



const AttributeDescriptions & ShaderVariableManager::getAttributeDescriptions() const{
	return attributes;
}

const UniformDescriptions & ShaderVariableManager::getUniformDescriptions() const{
	return uniforms;
}

const OutputDescriptions  & ShaderVariableManager::getOutputDescriptions() const{
	return outputs;
}

const UniformDescription & ShaderVariableManager::getUniformDescription(const std::string & name) throw (ShaderVariableDoesNotExistException) {
	uniform_desc_map::const_iterator i = uniform_ids.find(name);
	if(i != uniform_ids.end()) {
		return i->second;
	}else throw ShaderVariableDoesNotExistException(name);
}
const AttributeDescription & ShaderVariableManager::getAttributeDescription(const std::string & name) throw (ShaderVariableDoesNotExistException) {
	attribute_desc_map::const_iterator i = attribute_ids.find(name);
	if(i != attribute_ids.end()) {
		return i->second;
	}else throw ShaderVariableDoesNotExistException(name);
}
const OutputDescription & ShaderVariableManager::getOutputDescription(const std::string & name) throw (ShaderVariableDoesNotExistException) {
	output_desc_map::const_iterator i = output_ids.find(name);
	if(i != output_ids.end()) {
		return i->second;
	}else throw ShaderVariableDoesNotExistException(name);
}
static int uniform_counter = 0;
static int attribute_counter = 0;
static int output_counter = 0;

UniformDescription::UniformDescription(const UniformDescription & des) {
	id = des.id;
	name = std::string(des.name);
	description = std::string(des.description);
}

UniformDescription::UniformDescription(const std::string & name, const std::string & description){
	initialize(name,description);
}


UniformDescription::UniformDescription(const std::string & name){
	initialize(name,"");
}

void UniformDescription::initialize(const std::string & name, const std::string & description) {
	id = uniform_counter++;
	this->name = name;
	this->description = description;
}

const std::string UniformDescription::toString() const {
	std::stringstream s;
	s << "<UniformDescription " << name << " at [" << id << "]>";
	return s.str();
}

AttributeDescription::AttributeDescription(const AttributeDescription & des) {
	id = des.id;
	name = std::string(des.name);
	description = std::string(des.description);
}

AttributeDescription::AttributeDescription(const std::string & name, const std::string & description){
	initialize(name,description);
}


AttributeDescription::AttributeDescription(const std::string & name){
	initialize(name,"");
}

void AttributeDescription::initialize(const std::string & name, const std::string & description) {
	id = attribute_counter++;
	this->name = name;
	this->description = description;
}

const std::string AttributeDescription::toString() const {
	std::stringstream s;
	s << "<AttributeDescription " << name << " at [" << id << "]>";
	return s.str();
}

OutputDescription::OutputDescription(const OutputDescription & des) {
	id = des.id;
	name = std::string(des.name);
	description = std::string(des.description);
}

OutputDescription::OutputDescription(const std::string & name, const std::string & description){
	initialize(name,description);
}


OutputDescription::OutputDescription(const std::string & name){
	initialize(name,"");
}

void OutputDescription::initialize(const std::string & name, const std::string & description) {
	id = output_counter++;
	this->name = name;
	this->description = description;
}

const std::string OutputDescription::toString() const {
	std::stringstream s;
	s << "<OutputDescription " << name << " at [" << id << "]>";
	return s.str();
}


UniformDescription UniformDescription::MVP_MATRIX = UniformDescription("mvpMatrix");
UniformDescription UniformDescription::MV_MATRIX = UniformDescription("mvMatrix");
UniformDescription UniformDescription::COLOR = UniformDescription("uColor");
UniformDescription UniformDescription::COLOR_TEXTURE = UniformDescription("uColorTex");


AttributeDescription AttributeDescription::POSITION = AttributeDescription("vPosition");
AttributeDescription AttributeDescription::COLOR = AttributeDescription("vColor");
AttributeDescription AttributeDescription::TEXTURE_COORD_1 = AttributeDescription("vTexCoord1");
AttributeDescription AttributeDescription::NORMAL = AttributeDescription("vNormal");

OutputDescription OutputDescription::STDOUT = OutputDescription("stdout");
}

