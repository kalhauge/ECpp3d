#ifndef ECPP3DPRIMITIVES_H_
#define ECPP3DPRIMITIVES_H_

#include "draw/ECpp3dDrawable.h"

namespace ECpp3d {

class Square : public Drawable {
    static GLuint indicies[];
    static GLfloat pos[];
    static GLfloat tex[];
    static GLfloat color[];
    static GLfloat normal[];


    static Square * instance;
public:
    
    static Square * create();
    Square * initialize();

};


class Cube : public Drawable {
    static GLuint indicies[];
    static GLfloat pos[];
    static GLfloat tex[];
    static GLfloat color[];
    static GLfloat normal[];


    static Cube * instance;
public:
    
    static Cube * create();
    Cube * initialize();

}; 




}

#endif
