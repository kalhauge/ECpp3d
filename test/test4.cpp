/*
 * This test aims to hit CubeMaps, and Entities.
 */

#define TEST_NAME "Test 4"
#include "testenv.h"

using namespace ECpp3d;

Image * images;
TextureCube * cubetex;

Drawable * fullscreen;

ShaderProgram * program;

glm::mat4 projection;
glm::mat4 modelview = glm::mat4();


void setupGL() {
    try {
    OpenGLContext::initialize();
    OpenGLContext::loadStandardVariableDescription(); 
    OpenGLContext::printspecs(std::cout);
    OpenGLContext::SCREEN->initialize(new Area(0,0,600,600));

    projection = glm::perspective(45.0f,1.0f,0.05f,100.0f);


    // Image start
    images = Image::createCubeMapImages(
            Image::fromJPEG("cube_unwrapped.jpg"
                )); 
    
    glEnable(GL_CULL_FACE);
    //glCullFace(GL_FRONT);

    // Texure invocation
    cubetex = TextureCube::create()->initialize(images);
    // Drawables
    fullscreen = Cube::create()->initialize();

    // Programs
    program = ShaderProgram::fromPath("cubetest")->initialize();
    program->printActiveVariables(std::cout);
    
    
    modelview = glm::mat4();
    modelview = glm::translate(modelview,glm::vec3(0.0f,0.0f,-5.0f));
    modelview = glm::rotate(modelview,-45.0f,glm::vec3(1.0f,0.0f,0.0f));
 
   
    program->validate();

    OpenGLContext::checkForErrors();

    } catch (Exception & e) {
        std::cerr << e << std::endl;
    }
}

char loop() {
    OpenGLContext::SCREEN->clearColor(glm::vec4(0.5,0,0,1));
    program->use();
    modelview = glm::rotate(modelview,1.0f,glm::vec3(0.0f,1.0f,0.0f));
    program->attachUniform(UniformDescription::COLOR_TEXTURE,cubetex);
    program->attachUniform(UniformDescription::MVP_MATRIX,projection * modelview);




    fullscreen->draw();
    glfwSwapBuffers();
    return 1;
}


