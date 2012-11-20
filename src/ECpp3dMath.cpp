/*
 * ECpp3dMath.cpp
 *
 *  Created on: 20/11/2012
 *      Author: christian
 */

#include <sstream>
#include "ECpp3dMath.h"

namespace ECpp3d {

const std::string Scalar::toString() const {
	std::stringstream s;
	s << "<Scalar: " << value << ">";
	return s.str();
}

}
