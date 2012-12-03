/*
 * ECpp3dOpenGLContext.h
 *
 *  Created on: 03/12/2012
 *      Author: christian
 */

#ifndef ECPP3DOPENGLCONTEXT_H_
#define ECPP3DOPENGLCONTEXT_H_

#include "ECpp3dUtils.h"
#include "ECpp3dException.h"
#include "handlers/ECpp3dTexture.h"

namespace ECpp3d {

class OpenGLContext {
	static bool initialized;
	static Samplers samplers;
	static Samplers freeSamplers;
public:
	static void printspecs(std::ostream & out);
	static void checkForErrors() throw (OpenGLException);
	static bool isInitialized() {return initialized;}
	static void initialize() {
		initialized = true;
		samplers = Sampler::getSamplers();
		freeSamplers = Samplers(samplers);
	}

	static void finalize() {
		OpenGLHandler::finalize((Handlers*)&samplers);
	}

	static Sampler * getSampler() {
		return freeSamplers.pop_back();
	}

	static free(Sampler * sampler) {
		freeSamplers.push_back(sampler);
	}

	static GLint getInteger(GLenum e);

	static GLuint getMaxCombinedTextureImageUnits();
};

bool OpenGLContext::initialized = false;

inline GLint OpenGLContext::getInteger(GLenum e) {
	GLint a;
	glGetIntegerv(e,&a);
	return a;
}

inline GLuint OpenGLContext::getMaxCombinedTextureImageUnits(){
	return getInteger(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);
}

}

#endif /* ECPP3DOPENGLCONTEXT_H_ */
