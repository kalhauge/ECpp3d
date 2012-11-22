/*
 * ECpp3dEntity.cpp
 *
 *  Created on: 21/11/2012
 *      Author: christian
 */


#include "ECpp3dEntity.h"
#include "glm/gtc/matrix_inverse.hpp"
using namespace glm;

namespace ECpp3d {

Entity::Entity(){
	modelMatrix = mat4(1.0f);
}

Entity::~Entity() {
}

void Entity::createMatrices(const mat4 & projection, const mat4 & view) {
	mvMatrix = view * modelMatrix;
	mvpMatrix = projection * mvMatrix;
	nMatrix = inverseTranspose(mat3(mvMatrix));

	for(int i = 0; i < children.size(); ++i) {
		children[i]->createMatrices(projection,mvMatrix);
	}
}

void Entity::addChild(Entity * entity) {
	children.push_back(entity);
}



}  // namespace ECpp3d
