
#include "draw/ECpp3dDrawable.h"

namespace ECpp3d {

Drawable * Drawable::initialize(
        GLint n_verts    , GLfloat ** info,
        GLint n_indicies , GLuint * indicies,
        GLenum mode
    ) {
    mesh = VertexArray::create();
    
    Buffers buffers = Buffer::generateBuffers(5);

    ArrayBuffer * buffer; 

    buffer = ArrayBuffer::create(buffers[0])
        ->initialize(info[0],n_verts,3,GL_FLOAT,GL_STATIC_DRAW);

    mesh->add(AttributeDescription::POSITION,buffer);

    buffer = ArrayBuffer::create(buffers[1])
        ->initialize(info[1],n_verts,2,GL_FLOAT,GL_STATIC_DRAW);

    mesh->add(AttributeDescription::TEXTURE_COORD_1,buffer);

    buffer = ArrayBuffer::create(buffers[2])
        ->initialize(info[2],n_verts,3,GL_FLOAT,GL_STATIC_DRAW);

    mesh->add(AttributeDescription::COLOR,buffer);

    buffer = ArrayBuffer::create(buffers[3])
        ->initialize(info[3],n_verts,3,GL_FLOAT,GL_STATIC_DRAW);

    mesh->add(AttributeDescription::NORMAL,buffer);
    
    drawer = ElementArrayBuffer::create(buffers[4])
        ->initialize(indicies,n_indicies,mode,GL_UNSIGNED_INT,
                GL_STATIC_DRAW);

    mesh->initialize(n_verts);
    return this;
}

void Drawable::draw() const {
    mesh->bind();
    drawer->draw();
} 

}

