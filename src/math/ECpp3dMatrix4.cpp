/*
 * ECpp3dMatrix4.cpp
 *
 *  Created on: 20/11/2012
 *      Author: christian
 */

#include "math/ECpp3dMatrix4.h"


namespace ECpp3d {


Mat4 Mat4::indetity() {
	return Mat4().reset();
}

Mat4 Mat4::fustrum() {
}

Mat4 Mat4::ortigonal() {
}

Mat4& Mat4::reset() {
	for(int i = 0; i < 16; i++)
		values[i] = (i % 5 == 0 ? 1 : 0);
}

Mat4& Mat4::rotate(int axis, GLfloat degrees) {
}

Mat4& Mat4::scale(GLfloat scale) {
}

Mat4& Mat4::scale(GLfloat xs, GLfloat ys, GLfloat zs) {
}

Mat4& Mat4::move(GLfloat x, GLfloat y, GLfloat z) {
}

}

