/*
 * ECpp3dTexture.cpp
 *
 *  Created on: 01/12/2012
 *      Author: christian
 */


#include "handlers/ECpp3dTexture.h"

namespace ECpp3d {


const Texture2D * Texture2D::bound = 0;

Textures Texture::generateTextures(GLsizei number){
	GLuint locations[number];
	glGenBuffers(number,locations);

	Textures textures;

	for(int i = 0; i < number; ++i) {
		Texture * ntextures = new Texture(locations[i]);
		textures.push_back(ntextures);
	}

	return textures;
}

Texture * Texture::generateTexture(){
	return generateTextures(1)[0];
}


// Sampler

Samplers Sampler::getSamplers() {
	GLuint num_samplers = OpenGLContext::getMaxCombinedTextureImageUnits();
	Samplers samplers;
	for(int i = 0; i < num_samplers; ++i)
		samplers.push_back(new Sampler(i));

	return samplers;
}


// Texture 2D


void Texture2D::ensureBound() const{
	if(bound != this) {
		bound = this;
		glBindTexture(type,location);
	}
}

void Texture::finalize() {
	glDeleteTextures(1,&location);
}


void Texture2D::initiailize() {

}

}
