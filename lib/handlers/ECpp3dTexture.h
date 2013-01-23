/*
 * ECpp3dTexture.h
 *
 *  Created on: 27/11/2012
 *      Author: christian
 */

#ifndef ECPP3DTEXTURE_H_
#define ECPP3DTEXTURE_H_

#include "ECpp3dUtils.h"
#include "tools/ECpp3dImage.h"
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

	GLsizei format;
    
    Image * data;
    
	void setupTexture();
	Texture(GLuint location,GLenum type, GLenum bindtype);
	void initialize();
	void ensureSampler();

public:

	static Textures generateTextures(GLsizei number);
	static Texture * generateTexture();

    ~Texture();

	void attach(const Uniform & u);
	void freeSampler();
	void finalize();
	void validate() const throw (OpenGLException){};

	void setParameter(GLenum pname, GLint param);

	const std::string toString() const;

	GLsizei getHeight();
	GLsizei getWidth();
	GLsizei getDepth();

	void setBaseLevel(GLint level);
	void setMaxLevel(GLint level);
	void setMinimizeMethod(GLenum method);
	void setMagnifyMethod(GLenum method);

	void setWrappingS(GLenum method);
	void setWrappingT(GLenum method);
	void setWrappingR(GLenum method);
};

inline void Texture::setParameter(GLenum pname, GLint param) {
	glTexParameteri(type, pname,param);
}


class Sampler : public Object {
protected:

	static const Sampler * active;
	const GLuint activeid;
	Sampler(GLuint activeid) : activeid(activeid) {};

public:

	static Samplers getSamplers();
	GLuint getActiveId() const;
	const std::string toString() const;

	GLenum getActiveEnum() const {
		return GL_TEXTURE0 + getActiveId();
	}

	void ensureActive() const;
	void validate() const throw (OpenGLException){};

};

class Texture1D : public Texture {
	static const GLenum type = GL_TEXTURE_1D;
	static const GLenum bindtype = GL_SAMPLER_1D;
public:
	Texture1D(Texture * const texture) : Texture(texture->getLocation(),type,bindtype) {
		delete texture;
	}
    
    static Texture1D * create(Texture * const texture = Texture::generateTexture());

	Texture1D * initialize(Image * image,GLint internalformat = GL_RGBA);
    void pushImage();
};


class Texture2D : public Texture {
	static const GLenum type = GL_TEXTURE_2D;
	static const GLenum bindtype = GL_SAMPLER_2D;
public:
	Texture2D(Texture * const texture) : Texture(texture->getLocation(),type,bindtype) {
		delete texture;
	};
    
    
    void pushImage();
    
    static Texture2D * create(Texture * const texture = Texture::generateTexture());

	GLenum getBindType() const;
    
    Texture2D * initialize(Image * image,GLint internalformat = GL_RGBA);
	Texture2D * initialize(const std::string & filename, GLint internalformat = GL_RGBA) throw (IOException);
	Texture2D * initialize(GLsizei width, GLsizei height, GLint internalformat = GL_RGBA);
};


class TextureCube : public Texture {
	static const GLenum type = GL_TEXTURE_CUBE_MAP;
	static const GLenum bindtype = GL_SAMPLER_CUBE;
    
    Image * sides[6];
public:
	TextureCube(Texture * const texture) : Texture(texture->getLocation(),type,bindtype) {
		delete texture;
	};
    
    GLsizei getHeight();
	GLsizei getWidth();
	GLsizei getDepth();
    
    static TextureCube * create(Texture * const texture = Texture::generateTexture());

	GLenum getBindType() const;
	TextureCube * initialize(Image * sides[6],GLint internalformat= GL_RGBA);


};

}



#endif /* ECPP3DTEXTURE_H_ */
