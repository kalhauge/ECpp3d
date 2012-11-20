/*
 * ECpp3dMath.h
 *
 *  Created on: 19/11/2012
 *      Author: christian
 */

#ifndef ECPP3DMATH_H_
#define ECPP3DMATH_H_

#include "ECpp3dShaderProgram.h"

namespace ECpp3d {

class Scalar : public ShaderAttachable, public ECpp3dObject {
	GLfloat value;
public:
	Scalar(GLfloat value) {
		this->value = value;
	}

	inline Scalar & operator= (GLfloat a) {
		value = a;
		return *this;
	}

	inline Scalar & operator= (const Scalar & a) {
			value = a.value;
			return *this;
	}

	inline Scalar operator+(const Scalar & b) const {
		return Scalar(value + b.value);
	}

	inline Scalar & operator+=(const Scalar & b) {
		value += b.value;
		return *this;
	}

	inline Scalar operator-(const Scalar & b) const {
		return Scalar(value - b.value);
	}

	inline Scalar & operator-=(const Scalar & b) {
		value -= b.value;
		return *this;
	}

	inline Scalar operator*(const Scalar & b) const {
		return Scalar(value * b.value);
	}

	inline Scalar & operator*=(const Scalar & b) {
		value *= b.value;
		return *this;
	}

	inline Scalar operator/(const Scalar & b) const {
		return Scalar(value / b.value);
	}

	inline Scalar & operator/=(const Scalar & b) {
		value /= b.value;
		return *this;
	}


	inline void attachTo(const Uniform & uniform) const {
		glUniform1f(uniform.getIndex(),value);
	}
	inline GLfloat getValue() const {return value;}
	const std::string toString() const;
};

class Vec2 : public ShaderAttachable, public ECpp3dObject {

};

}


#endif /* ECPP3DMATH_H_ */
