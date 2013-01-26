#include <ECpp3d.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU

#include <GL/glfw.h>

void setupGL();

char loop();

int main(int argc, char ** argv)
{   
    if(!glfwInit()){ exit( EXIT_FAILURE);}

    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR,3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR,2);

    if( !glfwOpenWindow( 600,600, 0,0,0,0,0,0, GLFW_WINDOW ) ) {
         glfwTerminate();
         exit( EXIT_FAILURE );
     }
    
    glfwSetWindowTitle(TEST_NAME);
    GLfloat f[] = {0,0,0,1};
  
    setupGL(); 
    while(loop()); 

    glfwTerminate();
    return 1;
}
