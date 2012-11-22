/*
 * ECpp3dMatrix4.h
 *
 *  Created on: 20/11/2012
 *      Author: christian
 */

#ifndef ECPP3DMATRIX4_H_
#define ECPP3DMATRIX4_H_

#include "ECpp3dUtils.h"
#include "ECpp3dShaderProgram.h"

namespace ECpp3d {

class Mat4: public ShaderAttachable, public ECpp3dObject {
	GLfloat values[16];
public:
	Mat4();
	static Mat4 indetity();
	static Mat4 fustrum();
	static Mat4 ortigonal();

	Mat4 & reset();
	Mat4 & rotate(int axis, GLfloat degrees);
	Mat4 & scale(GLfloat scale);
	Mat4 & scale(GLfloat xs, GLfloat ys, GLfloat zs);
	Mat4 & move(GLfloat x, GLfloat y, GLfloat z);

	void attachTo(const Uniform & uniform) const;
};


inline void Mat4::attachTo(const Uniform & uniform) const {
	glUniformMatrix4fv(uniform.getIndex(), 1, GL_FALSE, values);
}

}

#endif /* ECPP3DMATRIX4_H_ */
