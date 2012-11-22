/*
 * ECpp3dVec4.h
 *
 *  Created on: 20/11/2012
 *      Author: christian
 */

#ifndef ECPP3DVEC4_H_
#define ECPP3DVEC4_H_

#include "ECpp3dMath.h"

namespace ECpp3d {

class Vec3 : public ShaderAttachable, public ECpp3dObject {
	GLfloat values[3];
public:
	Vec3(GLfloat x,GLfloat y,GLfloat z);
	Vec3();

	void attachTo(const Uniform & uniform) const;
};


}

#endif /* ECPP3DVEC4_H_ */
