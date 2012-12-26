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
#include <set>
namespace ECpp3d {

class OpenGLContext {
	static bool initialized;
	static Samplers samplers;
	static std::set<const Sampler*> freeSamplers;
public:
	static void printspecs(std::ostream & out);
	static void checkForErrors() throw (OpenGLException);
	static bool isInitialized() {return initialized;}
	static void initialize();

	static void resetSamplers();
	static void finalize() {
		OpenGLHandler::finalize((Handlers*)&samplers);
	}

	static const Sampler * getSampler();

	static void free(const Sampler * sampler);

	static GLsizei getSizeOf(GLenum e);

	static GLint getInteger(GLenum e);

	static GLuint getMaxCombinedTextureImageUnits();
};



inline GLint OpenGLContext::getInteger(GLenum e) {
	GLint a;
	glGetIntegerv(e,&a);
	return a;
}

}

#endif /* ECPP3DOPENGLCONTEXT_H_ */
