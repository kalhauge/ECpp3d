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
#include "handlers/ECpp3dFramebuffer.h"
#include "ECpp3dShaderProgram.h"
#include "handlers/ECpp3dVertexArray.h"
#include <set>
namespace ECpp3d {

class OpenGLContext {
	static bool initialized;
	static Samplers samplers;

	static const Area * viewport;

	static std::set<const Sampler*> freeSamplers;
	static ShaderVariableManager manager;
public:

    static Framebuffer * const SCREEN;
	static const UniformDescription & U(const std::string & name) throw (ShaderVariableDoesNotExistException);
	static const UniformDescription & U(const Uniform & uniform) throw (ShaderVariableDoesNotExistException);

	static const AttributeDescription & A(const std::string & name) throw (ShaderVariableDoesNotExistException);
	static const OutputDescription & O(const std::string & name) throw (ShaderVariableDoesNotExistException);

	static void load(const AttributeDescription & v) throw (ShaderVariableDoesExistException);
	static void load(const UniformDescription & v) throw (ShaderVariableDoesExistException);
	static void load(const OutputDescription & v) throw (ShaderVariableDoesExistException);
	static void loadStandardVariableDescription() throw (ShaderVariableDoesExistException);

	static const AttributeDescriptions & getAttributeDescriptions();
	static const UniformDescriptions & getUniformDescriptions();
	static const OutputDescriptions & getOutputDescriptions();

	static void printspecs(std::ostream & out);
	static void checkForErrors() throw (OpenGLException);
	static bool isInitialized() {return initialized;}
	static void initialize();

	static void resetSamplers();
	static void finalize() {
		OpenGLHandler::finalize((Handlers*)&samplers);
	}

	static void setViewport(const Area * const viewport);
	static void draw(const Framebuffer & buffer,const ShaderProgram & program,const VertexArray & object);
	static void draw(const Framebuffer * buffer,const ShaderProgram * program,const VertexArray * object);

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
