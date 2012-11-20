/*
 * ECpp3dEntity.h
 *
 *  Created on: 19/11/2012
 *      Author: christian
 */

#ifndef ECPP3DENTITY_H_
#define ECPP3DENTITY_H_

#include "ECpp3d.h"

namespace ECpp3d{

class Entity : public ECpp3dObject {
public:
	virtual void update();
	virtual void render() const;
};

}



#endif /* ECPP3DENTITY_H_ */
