/*
 * ECpp3dFramebuffer.h
 *
 *  Created on: 09/12/2012
 *      Author: christian
 */

#ifndef ECPP3DFRAMEBUFFER_H_
#define ECPP3DFRAMEBUFFER_H_

#include "ECpp3dUtils.h"
#include "handlers/ECpp3dTexture.h"
namespace ECpp3d {
class Framebuffer;

typedef std::vector<Framebuffer*> Framebuffers;

class Framebuffer : public OpenGLHandler{
	static const Framebuffer * const SCREEN;
	static const Framebuffer * bound;
	void ensureBound() const;
	Framebuffer(int location) : OpenGLHandler(location) {};
public:
	static Framebuffers generateFramebuffers(GLsizei number);
	static Framebuffer * generateFramebuffer();


	void attach(std::string name, Texture * texture);

	void validate() const throw (OpenGLException);
	void finalize() {};
};

}



#endif /* ECPP3DFRAMEBUFFER_H_ */
