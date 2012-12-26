/*
 * ECpp3dShaderVariable.cpp
 *
 *  Created on: 24/11/2012
 *      Author: christian
 */

#include "ECpp3dShaderVariable.h"
#include <sstream>
namespace ECpp3d {

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


void ShaderVariableManager::registerUniform(const UniformDescription & desc) throw (ShaderVariableDoesExistException){
	uniform_desc_map::iterator i = uniform_ids.find(desc.getName());
	if(i != uniform_ids.end())
		throw ShaderVariableDoesExistException(desc,i->second);
		uniform_ids.insert(uniform_desc_entry(desc.getName(),desc));
}

void ShaderVariableManager::registerAttribute(const AttributeDescription & desc) throw (ShaderVariableDoesExistException){
	attribute_desc_map::iterator i = attribute_ids.find(desc.getName());
	if(i != attribute_ids.end())
		throw ShaderVariableDoesExistException(desc,i->second);
	attribute_ids.insert(attribute_desc_entry(desc.getName(),desc));
}

void ShaderVariableManager::loadStandards() {
	registerUniform(UniformDescription::MVP_MATRIX);
	registerUniform(UniformDescription::MV_MATRIX);
	registerUniform(UniformDescription::COLOR);
	registerUniform(UniformDescription::COLOR_TEXTURE);
	registerAttribute(AttributeDescription::POSITION);
	registerAttribute(AttributeDescription::COLOR);
	registerAttribute(AttributeDescription::NORMAL);
	registerAttribute(AttributeDescription::TEXTURE_COORD_1);

}

const Uniform * ShaderVariableManager::getUniform(int variable_enum) const {
	std::map<int,Uniform>::const_iterator i =  uniforms.find(variable_enum);
	if(i == uniforms.end()) return 0;
	return &i->second;
}

const Attribute* ShaderVariableManager::getAttribute(int variable_enum) const {
	std::map<int,Attribute>::const_iterator i =  attributes.find(variable_enum);
	if(i == attributes.end()) return 0;
	return &i->second;
}

const Uniform * ShaderVariableManager::getUniform(
		const UniformDescription& desc) const {
	return getUniform(desc.getId());
}

const Attribute*  ShaderVariableManager::getAttribute(
		const AttributeDescription& desc) const {
	return getAttribute(desc.getId());
}

void ShaderVariableManager::loadVariables(std::vector<Uniform> in_uniforms,std::vector<Attribute> in_attributes) throw (ShaderVariableDoesNotExistException) {

	for(std::vector<Uniform>::iterator u = in_uniforms.begin();
		u != in_uniforms.end();
		++u) {
		uniform_desc_map::iterator i = uniform_ids.find(u->getName());
		if(i == uniform_ids.end()) throw ShaderVariableDoesNotExistException(u->getName());
		uniforms.insert(std::pair<int,Uniform>(i->second.getId(),*u));
	}

	for(std::vector<Attribute>::iterator a = in_attributes.begin();
		a != in_attributes.end();
		++a) {
		attribute_desc_map::iterator i = attribute_ids.find(a->getName());
		if(i == attribute_ids.end()) throw ShaderVariableDoesNotExistException(a->getName());
		attributes.insert(std::pair<int,Attribute>(i->second.getId(),*a));
	}
}


static int uniform_counter = 0;
static int attribute_counter = 0;

UniformDescription::UniformDescription(const UniformDescription & des) {
	id = des.id;
	name = std::string(des.name);
	description = std::string(des.description);
}

UniformDescription::UniformDescription(const std::string & name, const std::string & description){
	init(name,description);
}


UniformDescription::UniformDescription(const std::string & name){
	init(name,"");
}

void UniformDescription::init(const std::string & name, const std::string & description) {
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
	init(name,description);
}


AttributeDescription::AttributeDescription(const std::string & name){
	init(name,"");
}

void AttributeDescription::init(const std::string & name, const std::string & description) {
	id = attribute_counter++;
	this->name = name;
	this->description = description;
}

const std::string AttributeDescription::toString() const {
	std::stringstream s;
	s << "<AttributeDescription " << name << " at [" << id << "]>";
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
}

