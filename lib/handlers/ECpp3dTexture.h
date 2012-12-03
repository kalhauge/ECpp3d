/*
 * ECpp3dTexture.h
 *
 *  Created on: 27/11/2012
 *      Author: christian
 */

#ifndef ECPP3DTEXTURE_H_
#define ECPP3DTEXTURE_H_

#include "ECpp3dUtils.h"

namespace ECpp3d {
class Texture;
class Sampler;

typedef std::vector<Texture*> Textures;
typedef std::vector<Sampler*> Samplers;

class Texture : public OpenGLHandler {
protected:
	Texture(GLuint location)
	: OpenGLHandler(location) {};
public:
	static Textures generateTextures(GLsizei number);
	static Texture * generateTexture();

	void finalize();
	void validate() const throw (OpenGLException){};
};

class Sampler : public OpenGLHandler {
protected:
	Sampler(GLuint location)
		: OpenGLHandler(location) {};
public:
	static Samplers getSamplers();

	void initialize() {};
	void finalize() {};
	void validate() const throw (OpenGLException){};

};


class Texture2D : public Texture {
	static const GLenum type = GL_TEXTURE_2D;
	static const Texture2D * bound;
	void ensureBound() const;
public:
	Texture2D(Texture * const texture) : Texture(texture->getLocation()) {
		delete texture;
	};

	void initiailize();
};

}

#endif /* ECPP3DTEXTURE_H_ */
