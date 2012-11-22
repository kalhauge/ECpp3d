/*
 * ECpp3dScalar.h
 *
 *  Created on: 20/11/2012
 *      Author: christian
 */

#ifndef ECPP3DSCALAR_H_
#define ECPP3DSCALAR_H_

#include "ECpp3dUtils.h"
#include "ECpp3dShaderProgram.h"


namespace ECpp3d {

class Scalar : public ShaderAttachable, public ECpp3dObject {
	GLfloat value;
public:
	Scalar(GLfloat value);

	Scalar & operator=  (GLfloat a);
	Scalar & operator=  (const Scalar & a);

	Scalar	 operator+  (const Scalar & b) const;
	Scalar & operator+= (const Scalar & b);

	Scalar	 operator-  (const Scalar & b) const;
	Scalar & operator-= (const Scalar & b);

	Scalar	 operator*  (const Scalar & b) const;
	Scalar & operator*= (const Scalar & b);

	Scalar	 operator/  (const Scalar & b) const;
	Scalar & operator/= (const Scalar & b);

	GLfloat getValue() const;

	void attachTo(const Uniform & uniform) const;

	const std::string toString() const;
};



inline Scalar & Scalar::operator= (GLfloat a) {
	value = a;
	return *this;
}
inline Scalar & Scalar::operator= (const Scalar & a) {
	value = a.value;
	return *this;
}
inline Scalar Scalar::operator+(const Scalar & b) const {
	return Scalar(value + b.value);
}
inline Scalar & Scalar::operator+=(const Scalar & b) {
	value += b.value;
	return *this;
}
inline Scalar Scalar::operator-(const Scalar & b) const {
	return Scalar(value - b.value);
}
inline Scalar & Scalar::operator-=(const Scalar & b) {
	value -= b.value;
	return *this;
}
inline Scalar Scalar::operator*(const Scalar & b) const {
	return Scalar(value * b.value);
}
inline Scalar & Scalar::operator*=(const Scalar & b) {
	value *= b.value;
	return *this;
}
inline Scalar Scalar::operator/(const Scalar & b) const {
	return Scalar(value / b.value);
}
inline Scalar & Scalar::operator/=(const Scalar & b) {
	value /= b.value;
	return *this;
}

inline GLfloat Scalar::getValue() const {return value;}


}


#endif /* ECPP3DSCALAR_H_ */
