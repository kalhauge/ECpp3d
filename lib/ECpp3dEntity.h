/*
 * ECpp3dEntity.h
 *
 *  Created on: 19/11/2012
 *      Author: christian
 */

#ifndef ECPP3DENTITY_H_
#define ECPP3DENTITY_H_

#include "ECpp3dUtils.h"
#include "ECpp3dDraworder.h"
#include "ECpp3dDrawable.h"
#include "handlers/ECpp3dVertexArray.h"
#include <glm/glm.hpp>
#include <vector>
namespace ECpp3d{

class Entity : public Object, public Drawable {
// Important matrices
	glm::mat4 modelMatrix;
	glm::mat4 mvpMatrix;
	glm::mat4 mvMatrix;
	glm::mat3 nMatrix;

	std::vector<Entity*> children;

	VertexArray* info;

public:

	Entity();
	virtual ~Entity();

	void createMatrices(const glm::mat4 & projection, const glm::mat4 & view);

	virtual void update();
	virtual void render() const;

    void draw();
    
	void addChild(Entity * entity);
	glm::mat4 & editModelMatrix();
};


inline glm::mat4 & Entity::editModelMatrix() {
	return modelMatrix;
}

    
}



#endif /* ECPP3DENTITY_H_ */
