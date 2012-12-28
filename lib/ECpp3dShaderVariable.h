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
	Uniform(const Uniform & uniform);
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
	void initialize(const std::string & name, const std::string & description);
public:
	static UniformDescription MVP_MATRIX,MV_MATRIX,COLOR,COLOR_TEXTURE;

	UniformDescription(const UniformDescription & des);
	UniformDescription(const std::string & name, const std::string & description);
	UniformDescription(const std::string & name);
	const std::string toString() const;
};

class AttributeDescription : public VariableDescription {
	void initialize(const std::string & name, const std::string & description);
public:
	static AttributeDescription POSITION,COLOR,NORMAL,TEXTURE_COORD_1;

	AttributeDescription(const AttributeDescription & des);
	AttributeDescription(const std::string & name, const std::string & description);
	AttributeDescription(const std::string & name);
	const std::string toString() const;
};


class OutputDescription : public VariableDescription {
	void initialize(const std::string & name, const std::string & description);
public:
	static OutputDescription STDOUT;
	OutputDescription(const OutputDescription & des);
	OutputDescription(const std::string & name, const std::string & description);
	OutputDescription(const std::string & name);
	const std::string toString() const;
};

typedef std::vector<const UniformDescription*> UniformDescriptions;
typedef std::vector<const AttributeDescription*> AttributeDescriptions;
typedef std::vector<const OutputDescription*> OutputDescriptions;

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

	typedef std::map<const std::string, const OutputDescription> output_desc_map;
	typedef std::pair<const std::string, const OutputDescription> output_desc_entry;

	uniform_desc_map uniform_ids;
	attribute_desc_map attribute_ids;
	output_desc_map output_ids;

	std::vector<const UniformDescription*> uniforms;
	std::vector<const OutputDescription*> outputs;
	std::vector<const AttributeDescription*> attributes;
public:
	void registerUniform(const UniformDescription & description) throw (ShaderVariableDoesExistException);
	void registerAttribute(const AttributeDescription & description) throw (ShaderVariableDoesExistException);
	void registerOutput(const OutputDescription & description) throw (ShaderVariableDoesExistException);

	void loadStandards() throw(ShaderVariableDoesExistException);

	const UniformDescription & getUniformDescription(const std::string & name) throw (ShaderVariableDoesNotExistException);
	const AttributeDescription & getAttributeDescription(const std::string & name) throw (ShaderVariableDoesNotExistException);
	const OutputDescription & getOutputDescription(const std::string & name) throw (ShaderVariableDoesNotExistException);


	const UniformDescriptions & getUniformDescriptions() const;
	const AttributeDescriptions & getAttributeDescriptions() const;
	const OutputDescriptions & getOutputDescriptions() const;

};



}


#endif /* ECPP3DSHADERVARIABLE_H_ */
