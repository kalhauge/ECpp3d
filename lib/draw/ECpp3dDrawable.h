/*
 * ECpp3dDrawable.h
 *
 *  Created on: 13/01/2013
 *      Author: christian
 */

#ifndef ECPP3DDRAWABLE_H_
#define ECPP3DDRAWABLE_H_

#include "glm/glm.hpp" 
#include "handlers/ECpp3dVertexArray.h"

namespace ECpp3d {

// Interface: Drawable
//
// A drawable has a method to draw itself using a drawable. A drawable has
// no information about itself except the mesh and the drawer

class Drawable {
protected:
    VertexArray * mesh;
    ElementArrayBuffer * drawer;
    
public:
    Drawable * initialize(
            GLint n_verts, GLfloat ** info,
            GLint n_indicies, GLuint * indicies,
            GLenum mode);
    virtual void draw() const;
};

}
#endif /* ECPP3DDRAWABLE_H_ */
