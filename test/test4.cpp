/*
 * This test aims to hit CubeMaps, and Entities.
 */

#define TEST_NAME "Test 4"
#include "testenv.h"

using namespace ECpp3d;

Image * images;
TextureCube * cube;


void setupGL() {
    OpenGLContext::initialize();
    
    OpenGLContext::printspecs(std::cout);
    OpenGLContext::SCREEN->initialize(new Area(0,0,600,600));

    // Image start
    images = Image::createCubeMapImages(Image::fromJPEG("cube_unwrapped.jpg")); 
    cube = TextureCube::create()->initialize(&images);

    std::string names[] = {"Xp","Zp","Xm","Zm","Yp","Ym"};

    for (int i = 0; i < 6; i ++){
        images[i].toJPEG(names[i] + ".jpg");
    }
    // Texure invocation
}

char loop() {
    OpenGLContext::SCREEN->clearColor(glm::vec4(1,0,0,1));
    glfwSwapBuffers();
    return 1;
}


