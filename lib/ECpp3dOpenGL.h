//
//  ECpp3dOpenGL.h
//  ecpp3d
//
//  Created by Christian Gram Kalhauge on 04/11/12.
//  Copyright (c) 2012 Kalhauge. All rights reserved.
//

#ifndef ecpp3d_ECpp3dOpenGL_h
#define ecpp3d_ECpp3dOpenGL_h

/* #include <GL/gl.h> */
/* #include <GL/glu.h> */

#include <OpenGL/gl3.h>
#include <OpenGL/OpenGL.h>


/*  SPECIAL FUNCTIONS TO MAKE THE INTERACTION WITH OPENGL EASIER*/

namespace ECpp3d {

/* 
name: (type:GLenum) -> typeSize -> (size in bytes of type:int)
returns -1 if the type is not found
*/

int typeSize(GLenum type);
/* 
name: (format:GLenum) -> formatSize -> (number of fields used in format:int)
returns -1 if the format is not known;
*/

int formatSize(GLenum format);

/*
name: (type:T) -> getType -> (Enum descriping the type)
*/

template<typename T>
GLenum getType(T type);

}

#endif
