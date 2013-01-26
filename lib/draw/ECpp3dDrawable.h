/*
 * ECpp3dDrawable.h
 *
 *  Created on: 13/01/2013
 *      Author: christian
 */

#ifndef ECPP3DDRAWABLE_H_
#define ECPP3DDRAWABLE_H_

#include "glm/glm.hpp" 

namespace ECpp3d {

class Drawable {
public:
	virtual void draw(const glm::mat4 & projection, const glm::mat4 & view) const = 0;
};

}
#endif /* ECPP3DDRAWABLE_H_ */