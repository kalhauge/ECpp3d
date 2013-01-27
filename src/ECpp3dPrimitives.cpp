
#include "draw/ECpp3dPrimitives.h"
#include "Ecpp3dutils.h"
namespace ECpp3d {


GLuint Square::indicies[] = {
    1,0,3,3,2,1
};

GLfloat Square::pos[] = {
    -1,  1,  0,
     1,  1,  0,
     1, -1,  0,
    -1, -1,  0 
};

GLfloat Square::tex[] = {
    0,  1,
    1,  1,
    1,  0,
    0,  0
};

GLfloat Square::color[] = {
    0,  1,  1, 
    1,  1,  0, 
    1,  0,  1, 
    0,  0,  1
};

GLfloat Square::normal[] = {
    0,  0,  -1, 
    0,  0,  -1, 
    0,  0,  -1, 
    0,  0,  -1
};

Square * Square::instance = 0;

Square * Square::create() {
    if(!instance) {
        instance = new Square();
    }
    return instance;
}

Square * Square::initialize() {
    GLfloat * a[] = {pos,tex,color,normal}; 
    Drawable::initialize(4,a,6,indicies,GL_TRIANGLES);
    return this;
}

GLuint Cube::indicies[] = {
   0, 1, 2, 2, 3, 0,
   4, 5, 6, 6, 7, 4,
   8, 9,10,10,11, 8,
  12,13,14,14,15,12,
  16,17,18,18,19,16,
  20,21,22,22,23,20,

};

GLfloat Cube::pos[] = {
    -1, -1,  1, // P1
     1, -1,  1, // P2 
     1,  1,  1, // P3
    -1,  1,  1, // P4
                
     1, -1, -1, // P8
    -1, -1, -1, // P7
    -1,  1, -1, // P5
     1,  1, -1, // P6

     1,  1,  1, // P3
     1,  1, -1, // P6
    -1,  1, -1, // P5
    -1,  1,  1, // P4

    -1, -1,  1, // P1
    -1, -1, -1, // P7
     1, -1, -1, // P8
     1, -1,  1, // P2 

     1, -1,  1, // P2 
     1, -1, -1, // P8
     1,  1, -1, // P6
     1,  1,  1, // P3
                
    -1, -1, -1, // P7
    -1, -1,  1, // P1
    -1,  1,  1, // P4
    -1,  1, -1, // P5

};

GLfloat Cube::tex[] = {
    0,  0,
    1,  0,
    1,  1,
    0,  1,

    0,  0,
    1,  0,
    1,  1,
    0,  1,

    0,  0,
    1,  0,
    1,  1,
    0,  1,

    0,  0,
    1,  0,
    1,  1,
    0,  1,

    0,  0,
    1,  0,
    1,  1,
    0,  1,

    0,  0,
    1,  0,
    1,  1,
    0,  1


};

GLfloat Cube::color[] = {
    0,  0,  1, 
    0,  0,  1, 
    0,  0,  1, 
    0,  0,  1,

    0,  0,  1, 
    0,  0,  1, 
    0,  0,  1, 
    0,  0,  1,

    0,  1,  0, 
    0,  1,  0, 
    0,  1,  0, 
    0,  1,  0,

    0,  1,  0, 
    0,  1,  0, 
    0,  1,  0, 
    0,  1,  0,

    1,  0,  0, 
    1,  0,  0, 
    1,  0,  0, 
    1,  0,  0,

    1,  0,  0, 
    1,  0,  0, 
    1,  0,  0, 
    1,  0,  0

};

GLfloat Cube::normal[] = {
    0,  0,  1, 
    0,  0,  1, 
    0,  0,  1, 
    0,  0,  1,

    0,  0, -1, 
    0,  0, -1, 
    0,  0, -1, 
    0,  0, -1,

    0,  1,  0, 
    0,  1,  0, 
    0,  1,  0, 
    0,  1,  0,

    0, -1,  0, 
    0, -1,  0, 
    0, -1,  0, 
    0, -1,  0,

    1,  0,  0, 
    1,  0,  0, 
    1,  0,  0, 
    1,  0,  0,

   -1,  0,  0, 
   -1,  0,  0, 
   -1,  0,  0, 
   -1,  0,  0

};

Cube * Cube::instance = 0;

Cube * Cube::create() {
    if(!instance) {
        instance = new Cube();
    }
    return instance;
}

Cube * Cube::initialize() {
    GLfloat * a[] = {pos,tex,color,normal}; 
    Drawable::initialize(24,a,36,indicies,GL_TRIANGLES);
    return this;
}




}


