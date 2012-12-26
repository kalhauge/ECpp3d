/*
 * ECpp3dShaderVariable.h
 *
 *  Created on: 24/11/2012
 *      Author: christian
 */

#ifndef ECPP3DSHADERVARIABLE_H_
#define ECPP3DSHADERVARIABLE_H_

#include "ECpp3dUtils.h"
#include <map>
#include <vector>
#include <string>
#include <glm/glm.hpp>

namespace ECpp3d {

class ShaderVariable : public Object {
protected:
	std::string name;
	GLenum type;
	GLuint index;
	GLint size;
public:
	inline GLuint getIndex() const {return index;}
	const std::string& getName() const { return name;}
	GLint getSize() const { return size;}
	GLenum getType() const { return type;}
};

class Uniform : public ShaderVariable {
public:
	Uniform(GLuint program_id,GLuint index);
	virtual const std::string toString() const;
};

class Attribute : public ShaderVariable {
public:
	Attribute(GLuint program_id,GLuint index);
	virtual const std::string toString() const;
};


class VariableDescription : public Object {
protected:
	int id;
	std::string name;
	std::string description;
public:
	const std::string& getDescription() const { return description; }
	int getId() const {return id;}
	const std::string& getName() const { return name;}
};


class UniformDescription : public VariableDescription {
	void init(const std::string & name, const std::string & description);
public:
	static UniformDescription MVP_MATRIX,MV_MATRIX,COLOR,COLOR_TEXTURE;

	UniformDescription(const UniformDescription & des);
	UniformDescription(const std::string & name, const std::string & description);
	UniformDescription(const std::string & name);
	const std::string toString() const;
};

class AttributeDescription : public VariableDescription {
	void init(const std::string & name, const std::string & description);
public:
	static AttributeDescription POSITION,COLOR,NORMAL,TEXTURE_COORD_1;

	AttributeDescription(const AttributeDescription & des);
	AttributeDescription(const std::string & name, const std::string & description);
	AttributeDescription(const std::string & name);
	const std::string toString() const;
};


class ShaderVariableException : public Exception {

};

class ShaderVariableDoesExistException : public ShaderVariableException {
public:
	ShaderVariableDoesExistException(const VariableDescription & n, const VariableDescription & o);
};

class ShaderVariableDoesNotExistException : public ShaderVariableException {
public:
	ShaderVariableDoesNotExistException(const std::string & name);
};

class ShaderVariableManager : public Object {

protected:
	typedef std::map<const std::string, const UniformDescription> uniform_desc_map;
	typedef std::pair<const std::string, const UniformDescription> uniform_desc_entry;

	typedef std::map<const std::string, const AttributeDescription> attribute_desc_map;
	typedef std::pair<const std::string, const AttributeDescription> attribute_desc_entry;

	uniform_desc_map uniform_ids;
	attribute_desc_map attribute_ids;
	std::map<int,Uniform> uniforms;
	std::map<int,Attribute> attributes;
public:
	void registerUniform(const UniformDescription & description) throw (ShaderVariableDoesExistException);
	void registerAttribute(const AttributeDescription & description) throw (ShaderVariableDoesExistException);
	const Uniform * getUniform(int variable_enum) const;
	const Attribute * getAttribute(int variable_enum) const;
	const Uniform * getUniform(const UniformDescription & desc) const;
	const Attribute * getAttribute(const AttributeDescription & desc) const;
	void loadStandards();
	void loadVariables(std::vector<Uniform> uniforms,std::vector<Attribute> attributes) throw (ShaderVariableDoesNotExistException);
};



}


#endif /* ECPP3DSHADERVARIABLE_H_ */
