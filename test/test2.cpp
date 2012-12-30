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


ShaderProgram * calculator;

VertexArray * fullwindow_rect;

ArrayBuffer * position;
Texture1D * color;
Area * screen_size = new Area(0,0,600,600);
UniformDescription LIMIT("limit");
UniformDescription ITERATION("iteration");


void makeGradient(){
	Texture1D::gradient gradient;
	gradient.push_back(Texture1D::gradvector(0,glm::vec4(0,1,0,1)));
	gradient.push_back(Texture1D::gradvector(1,glm::vec4(1,0,0,1)));
	color = Texture1D::createLinearGradient(Texture::generateTexture(),512,gradient);
	color->setWrappingS(GL_CLAMP_TO_EDGE);
}

void setupGL() {
	glClearColor(0,0,1,1);
	OpenGLContext::initialize();
	Framebuffer::SCREEN->initialize(screen_size);
	OpenGLContext::loadStandardVariableDescription();
	OpenGLContext::load(LIMIT);
	OpenGLContext::load(ITERATION);

	OpenGLContext::printspecs(cout);
	try {

		fullwindow_rect = VertexArray::generateVertexArray();
		position = new ArrayBuffer(Buffer::generateBuffer());
		position->initialize(pos,6,2,GL_FLOAT,GL_STATIC_DRAW);
		fullwindow_rect->add(AttributeDescription::POSITION,position);

		makeGradient();

		calculator = ShaderProgram::fromPath("./simple_mandelbrot");

		calculator->initialize();
		fullwindow_rect->initialize(6);

		calculator->attachUniform(UniformDescription::COLOR_TEXTURE,color);
		glm::mat4 mvp = glm::translate(glm::scale(glm::mat4(),glm::vec3(1.5f,1.5f,1.5f)),glm::vec3(-0.5f,0,0));
		calculator->attachUniform(UniformDescription::MVP_MATRIX,mvp);

		calculator->printActiveVariables(cout);

		fullwindow_rect->validate();
		calculator->validate();
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
	    glfwSetWindowTitle("Mandelbrot test");
	    for(int i = 0; i < 1000; ++i){
	    	calculator->attachUniform(LIMIT,i);
	    	OpenGLContext::draw(Framebuffer::SCREEN,calculator,fullwindow_rect);
	    	glDrawArrays(GL_TRIANGLES,0,6);
	    	OpenGLContext::checkForErrors();
	    	glfwSwapBuffers();
	    }
	    glfwTerminate();
	    return 1;
}
