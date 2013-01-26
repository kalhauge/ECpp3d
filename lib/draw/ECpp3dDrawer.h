
#ifndef ECPP3DDRAWER_H_
#define ECPP3DDRAWER_H_

#include "ECpp3dUtils.h"
#include "handlers/ECpp3dFramebuffer.h"
#include "ECpp3dShaderProgram.h"
#include "ECpp3dDrawable.h"
#include <list>

namespace ECpp3d {

class Drawer : public Object {
    
    Framebuffer & canvas;
    ShaderProgram & program;
    
    std::list<const Drawable*> drawables;

    public:
    
    Drawer(ShaderProgram * program, Framebuffer * canvas); 

    void add(const Drawable * d);
    void drawAll() const;
    

}; 

}
