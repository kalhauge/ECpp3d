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

class Texture : public OpenGLHandler {
	GLenum type;
	GLuint location;
public:

	void finalize();
	void validate() const throw (OpenGLException);
};


class Texture2d : public Texture {
static GLuint location;
public:

};

}

#endif /* ECPP3DTEXTURE_H_ */
