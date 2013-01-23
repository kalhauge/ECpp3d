//
//  main.cpp
//  ECpp3dTest
//
//  Created by Christian Gram Kalhauge on 04/11/12.
//  Copyright (c) 2012 Kalhauge. All rights reserved.
//

#include <iostream>
#include <ECpp3d.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#include <GL/glfw.h>
#include <iterator>

using namespace std;
using namespace ECpp3d;


ShaderProgram * program;

static const GLfloat pos[] = {-1 , -1, 0,
							  -1 ,  1, 0,
							   1 , -1, 0,
							   1 , -1, 0,
							  -1 ,  1, 0,
							   1 ,  1, 0,
};

static const GLfloat tex[] = {0 , 0,
							  0 , 1,
							  1 , 0,
							  1 , 0,
							  0 , 1,
							  1 , 1,
};


VertexArray * rect;


Texture * texture;

Framebuffer * offscreen;
Texture2D * offscreen_image1;
Texture2D * offscreen_image2;

glm::mat4 projection;
glm::mat4 modelview;

void setupGL(){
    glClearColor(1.0f, 0.5f, 0.0f, 1.0f);

    OpenGLContext::initialize();
    OpenGLContext::loadStandardVariableDescription();
    OpenGLContext::printspecs(cout);

    projection = glm::perspective(45.0f,1.0f,1.0f,100.0f);


    Buffers arrays = Buffer::generateBuffers(2);
    ArrayBuffer * positions = new ArrayBuffer(arrays[0]);
    ArrayBuffer * texCoords = new ArrayBuffer(arrays[1]);

    positions->initialize(pos,6,3,GL_FLOAT,GL_STATIC_DRAW);
    texCoords->initialize(tex,6,2,GL_FLOAT,GL_STATIC_DRAW);

    rect = VertexArray::generateVertexArray();

    rect->add(AttributeDescription::POSITION,positions);
    rect->add(AttributeDescription::TEXTURE_COORD_1,texCoords);

    rect->initialize(6);

    Image::gradient grad;
    grad.push_back(Image::gradvector(0,glm::vec4(1,0,0,1)));
    grad.push_back(Image::gradvector(0.5,glm::vec4(0,0,1,1)));
    grad.push_back(Image::gradvector(1,glm::vec4(0,1,0,1)));
    texture = Texture1D::create()->initialize(Image::fromGradient(512,grad));
    try {
      texture = Texture2D::create()->initialize("./crate.jpg");

      offscreen_image1 = Texture2D::create()->initialize(1024,1024);
      offscreen_image2 = Texture2D::create()->initialize(1024,1024);

      offscreen = Framebuffer::generateFramebuffer();
      Area * area = new Area(0,0,1024,1024);
      offscreen->initialize(area);
      program = ShaderProgram::fromPath("./simple");
      program->initialize();

      cout << program->getNumberOfActiveUniforms() << endl;

      program->attachUniform(UniformDescription::MVP_MATRIX,projection * modelview);
      program->attachUniform(UniformDescription::COLOR,glm::vec4(1.0f,0.5f,0.2f,1.0f));
      program->attachUniform(UniformDescription::COLOR_TEXTURE,texture);

      program->printActiveVariables(cout);

      rect->validate();
      program->validate();
      OpenGLContext::checkForErrors();

    } catch(Exception & e) {
      cerr << e << endl;
      exit(-1);
    }
}


int main(int argc, char ** argv)
{   
    if(!glfwInit()){ exit( EXIT_FAILURE);}

    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR,3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR,2);

    if( !glfwOpenWindow( 600,600, 0,0,0,0,0,0, GLFW_WINDOW ) ) {
         glfwTerminate();
         exit( EXIT_FAILURE );
     }
    
    setupGL();
    glfwSetWindowTitle("TEST 1");
    Framebuffer::SCREEN->setViewport(new Area(0,0,600,600));
    GLfloat f[] = {0,0,0,1};

    cout << texture << endl;
    cout << offscreen_image1 <<endl;
    cout << offscreen_image2 <<endl;

    Texture2D * drawtexture = offscreen_image1;
    Texture2D * readtexture = offscreen_image2;

    program->attachUniform(UniformDescription::COLOR_TEXTURE,texture);
    glm::vec4 color(0.5f,0.5f,0.8f,1);
    glm::vec4 black(0,0,0,1);

    offscreen->attach(0,drawtexture);
    offscreen->clearColor(color);
    OpenGLContext::draw(offscreen,program,rect);
    glDrawArrays(GL_TRIANGLES,0,6);

    program->attachUniform(UniformDescription::COLOR_TEXTURE,drawtexture);

    glViewport(0,0,600,600);
    Framebuffer::SCREEN->clearColor(black);
    OpenGLContext::draw(Framebuffer::SCREEN,program,rect);
    glDrawArrays(GL_TRIANGLES,0,6);
    int x = 0;
    while(true) for(GLclampf i = 0; i < 1; i += 1.0/1000){
    	x = x ? 0 : 1;
    	color = glm::vec4(glm::sin(i*100),glm::cos(i*100),glm::sin(i*10),1);
        modelview = glm::mat4();
        modelview = glm::translate(modelview,glm::vec3(0.0f,0.0f,-3.0f));
        modelview = glm::rotate(modelview,360.0f*i,glm::vec3(0.0f,1.0f,0.0f));
        program->attachUniform(UniformDescription::MVP_MATRIX,projection * modelview);

        {
        	Texture2D * tmp = readtexture;
        	readtexture = drawtexture;
        	drawtexture = tmp;
        	offscreen->attach(0,drawtexture);
        	program->attachUniform(UniformDescription::COLOR_TEXTURE,readtexture);
        }

        offscreen->clearColor(color);
        OpenGLContext::draw(offscreen,program,rect);
        glDrawArrays(GL_TRIANGLES,0,6);

        program->attachUniform(UniformDescription::COLOR_TEXTURE,drawtexture);
        Framebuffer::SCREEN->clearColor(black);
        OpenGLContext::draw(Framebuffer::SCREEN,program,rect);
    	glDrawArrays(GL_TRIANGLES,0,6);
    	OpenGLContext::checkForErrors();
    	glfwSwapBuffers();
    }
    glfwTerminate();
    return 1;
}
