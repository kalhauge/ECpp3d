/*
 * ECpp3dTexture.h
 *
 *  Created on: 27/11/2012
 *      Author: christian
 */

#ifndef ECPP3DTEXTURE_H_
#define ECPP3DTEXTURE_H_

#include "ECpp3dUtils.h"
#include "ECpp3dShaderVariable.h"
#include <glm/glm.hpp>
namespace ECpp3d {
class Texture;
class Sampler;

typedef std::vector<Texture*> Textures;
typedef std::vector<Sampler*> Samplers;

class Texture : public OpenGLHandler {
	Texture(GLuint location);
protected:
	const Sampler * sampler;
	const GLenum type;
	const GLenum bindtype;
	Texture(GLuint location,GLenum type, GLenum bindtype);
	void initialize();
	void ensureSampler();
public:
	static Textures generateTextures(GLsizei number);
	static Texture * generateTexture();

	void attach(const Uniform & u);

	void freeSampler();
	void finalize();
	void validate() const throw (OpenGLException){};
};


class Sampler : public Object {
protected:

	static const Sampler * active;
	const GLuint activeid;
	Sampler(GLuint activeid) : activeid(activeid) {};

public:

	static Samplers getSamplers();
	GLuint getActiveId() const;

	GLenum getActiveEnum() const {
		return GL_TEXTURE0 + getActiveId();
	}

	void ensureActive() const;
	void validate() const throw (OpenGLException){};

};

class Texture1D : public Texture {
	static const GLenum type = GL_TEXTURE_1D;
	static const GLenum bindtype = GL_TEXTURE_BINDING_1D;
public:
	Texture1D(Texture * const texture) : Texture(texture->getLocation(),type,bindtype) {
		delete texture;
	}


	typedef std::pair<float,glm::vec4> gradvector;
	typedef std::vector<gradvector> gradient;

	static Texture1D * createLinearGradient(Texture * texture,int size, const gradient & description );


	void initialize(const std::vector<glm::vec4> & data);
};


class Texture2D : public Texture {
	static const GLenum type = GL_TEXTURE_2D;
	static const GLenum bindtype = GL_TEXTURE_BINDING_2D;
public:
	Texture2D(Texture * const texture) : Texture(texture->getLocation(),type,bindtype) {
		delete texture;
	};


	GLenum getBindType() const;
	void initiailize();
};

}

#endif /* ECPP3DTEXTURE_H_ */
