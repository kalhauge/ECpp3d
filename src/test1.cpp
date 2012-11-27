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

#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#include <GL/glfw.h>
#include <iterator>

using namespace std;
using namespace ECpp3d;


ShaderProgram * program;

const char * fragment = 
  "#version 150\n" 
  "out vec4 fragColor;"
  "uniform vec4 uColor;"
  "void main(void)"
  "{"
  "    fragColor = uColor;"
  "}";


const char * vertex =
  "#version 150\n"
  "uniform mat4 mvpMatrix;"
 
  "in vec4 vPosition;"
 
  "void main()"
  "{"   
    "gl_Position = mvpMatrix * vPosition;"
  "}";

static const GLfloat pos[] = {-0.5f,-0.5f,0,0.5f,0.5f,-0.5f};


VertexArray positions;

void setupGL(){
    glClearColor(1.0f, 0.5f, 0.0f, 1.0f);

    printspecs(cout);

    positions = VertexArray::generateVertexArray();
    positions.initialize(2,3,pos);

    try {
      program = new ShaderProgram();
      program->setFragmentShaderCode(fragment);
      program->setVertexShaderCode(vertex);
      program->compile();
      program->initialize();

      cout << program->getNumberOfActiveUniforms() << endl;

      program->attachUniform(UniformDescription::MVP_MATRIX,glm::mat4());
      program->attachUniform(UniformDescription::COLOR,glm::vec4(1.0f,0.5f,0.2f,1.0f));

      program->attachAttribute(AttributeDescription::POSITION,positions);

      cout << "Uniforms [";
      vector<Uniform> uniforms = program->getActiveUniformList();
      copy(uniforms.begin(),uniforms.end(),ostream_iterator<Uniform>(cout, ", "));
      cout << "]" << endl;

      cout << "Attributes [";
      vector<Attribute> attributes = program->getActiveAttributeList();
      copy(attributes.begin(),attributes.end(),ostream_iterator<Attribute>(cout, ", "));
      cout << "]" << endl;


    } catch(Exception & e) {
      cerr << e << endl;
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

    glfwSetWindowTitle("GLFW Testing");

    GLfloat f[] = {0,0,0,1};
    while(true) for(GLclampf i = 0; i < 1; i += 1.0/1000){
    	f[0] = i; f[1] = i; f[2] = i-1;
    	glClearColor(f[0],f[1],f[2],f[3]);
    	glClear(GL_COLOR_BUFFER_BIT);
    	program->ensureUsed();
    	glDrawArrays(GL_TRIANGLES,0,3);

    	glfwSwapBuffers();
    }
    glfwTerminate();
    return 1;
}
