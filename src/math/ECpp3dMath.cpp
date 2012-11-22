/*
 * ECpp3dMath.cpp
 *
 *  Created on: 20/11/2012
 *      Author: christian
 */

#include <sstream>
#include "math/ECpp3dMath.h"

namespace ECpp3d {

Scalar::Scalar(GLfloat value) {
	this->value = value;
}

const std::string Scalar::toString() const {
	std::stringstream s;
	s << "<Scalar: " << value << ">";
	return s.str();
}

void Scalar::attachTo(const ECpp3d::Uniform & uniform) const {
	glUniform1f(uniform.getIndex(),value);
}

}
