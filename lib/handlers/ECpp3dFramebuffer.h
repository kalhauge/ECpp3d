/*
 * ECpp3dFramebuffer.h
 *
 *  Created on: 09/12/2012
 *      Author: christian
 */

#ifndef ECPP3DFRAMEBUFFER_H_
#define ECPP3DFRAMEBUFFER_H_

#include "ECpp3dUtils.h"
#include "ECpp3dShaderVariable.h"
#include "handlers/ECpp3dTexture.h"
#include <map>
namespace ECpp3d {
class Framebuffer;

typedef std::vector<Framebuffer*> Framebuffers;

class Framebuffer : public OpenGLHandler{

	static const Framebuffer * bound;

	const Area * viewport;

	Framebuffer(int location) : OpenGLHandler(location), viewport(0){};
public:
	static Framebuffer * const SCREEN;

	void bind(bool force = false) const;

	static Framebuffers generateFramebuffers(GLsizei number);
	static Framebuffer * generateFramebuffer();

	void initialize(const Area * const viewport) {
		setViewport(viewport);
	};

	void setViewport(const Area  * const area);

	void attach(int i,const Texture2D * const texture);
	void clearColor(const glm::vec4 & color);

	void makedrawable() const;

	void validate() const throw (OpenGLException);
	void finalize() {};
};

}



#endif /* ECPP3DFRAMEBUFFER_H_ */
