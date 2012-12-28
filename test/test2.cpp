/*
 * test2.cpp
 *
 *  Created on: 26/12/2012
 *      Author: christian
 */

#include <ECpp3d.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#include <GL/glfw.h>

#include <iterator>

using namespace ECpp3d;
using namespace std;

static const GLfloat pos[] = {-1 , -1,
							  -1 ,  1,
							   1 , -1,
							   1 , -1,
							  -1 ,  1,
							   1 ,  1,
};


ShaderProgram * program;
VertexArray * screen;
ArrayBuffer * position;
Texture1D * color;
UniformDescription LIMIT("limit");
UniformDescription ITERATION("iteration");
void setupGL() {
	glClearColor(0,0,1,1);
	OpenGLContext::initialize();
	OpenGLContext::printspecs(cout);
	try {

		screen = VertexArray::generateVertexArray();
		position = new ArrayBuffer(Buffer::generateBuffer());
		position->initialize(pos,6,2,GL_FLOAT,GL_STATIC_DRAW);
		screen->add(AttributeDescription::POSITION,position);

		Texture1D::gradient gradient;
		gradient.push_back(Texture1D::gradvector(0,glm::vec4(0,1,0,1)));
		gradient.push_back(Texture1D::gradvector(1,glm::vec4(1,0,0,1)));
		color = Texture1D::createLinearGradient(Texture::generateTexture(),512,gradient);
		color->setWrappingS(GL_CLAMP_TO_EDGE);

		program = ShaderProgram::fromFileLocations("./simple_mandelbrot.vs","./step_mandelbrot.fs");

		program->getVariableManager().registerUniform(LIMIT);
		program->getVariableManager().registerUniform(ITERATION);

		program->initialize();
		screen->initialize(6);

		program->attachUniform(UniformDescription::COLOR_TEXTURE,color);
		glm::mat4 mvp = glm::translate(glm::scale(glm::mat4(),glm::vec3(1.5f,1.5f,1.5f)),glm::vec3(-0.5f,0,0));
		program->attachUniform(UniformDescription::MVP_MATRIX,mvp);

		program->printVariables(cout);

		screen->validate();
		program->validate();
		OpenGLContext::checkForErrors();
	} catch (Exception e) {
		cout << e << endl;
	}

}

int main(){
	if(!glfwInit()){ exit( EXIT_FAILURE);}

	    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR,3);
	    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR,2);

	    if( !glfwOpenWindow( 600,600, 0,0,0,0,0,0, GLFW_WINDOW ) ) {
	         glfwTerminate();
	         exit( EXIT_FAILURE );
	     }

	    setupGL();
	    glfwSetWindowTitle("GLFW Testing");
    	program->use();
    	screen->bind();
	    for(int i = 0; i < 1000; ++i){
	    	glClear(GL_COLOR_BUFFER_BIT);
	    	program->attachUniform(ITERATION,i);
	    	program->attachUniform(LIMIT,1000);
	    	glDrawArrays(GL_TRIANGLES,0,6);
	    	OpenGLContext::checkForErrors();
	    	glfwSwapBuffers();
	    }
	    glfwTerminate();
	    return 1;
}
