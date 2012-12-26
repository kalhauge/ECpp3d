/*
 * ECpp3dRenderbuffer.h
 *
 *  Created on: 16/12/2012
 *      Author: christian
 */

#ifndef ECPP3DRENDERBUFFER_H_
#define ECPP3DRENDERBUFFER_H_

#include "ECpp3dUtils.h"

namespace ECpp3d {

class Renderbuffer : public OpenGLHandler{
	Renderbuffer(int location) : OpenGLHandler(location) {};
public:
};

}


#endif /* ECPP3DRENDERBUFFER_H_ */
