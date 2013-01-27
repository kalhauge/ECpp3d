/*#include "draw/ECpp3dDrawer.h"


namespace ECpp3d{


Drawer::Drawer(ShaderProgram * program, Framebuffer * canvas)
    : canvas(*canvas),program(*program) {
    
}

void Drawer::add(const Drawable * e) {
    drawables.push_back(e);
}

void Drawer::drawAll() const {
    std::list<const Drawable*>::const_iterator i;
    for(i = drawables.begin(); i != entities.end(); ++i) {
        (*i)->draw();
    }
}



}*/
