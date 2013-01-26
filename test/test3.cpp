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

static const GLfloat tex[] = {0 ,  0,
							  0 ,  1,
							  1 ,  0,
							  1 ,  0,
							  0 ,  1,
							  1 ,  1,
};


ShaderProgram * calculator;
ShaderProgram * viewer;

VertexArray * fullwindow_rect;

Framebuffer * offscreen;

Texture2D * zValues[2];

ArrayBuffer * texCoord;
ArrayBuffer * position;

Texture1D * color;
Area * screen_size = new Area(0,0,600,600);
Area * texture_size = new Area(0,0,2048,2048);

struct screen_matrices{
	glm::mat4 translate;
	glm::mat4 scale;
	glm::mat4 aspect;
} smatrix;

glm::mat4 s2t = glm::translate(glm::mat4(), glm::vec3(0.5,0.5,0.5)) * glm::scale(glm::mat4(), glm::vec3(0.5f,0.5f,0.5f));
struct texture_matrices {
	glm::mat4 translate;
	glm::mat4 scale;
	glm::mat4 F_matrix;
} tmatrix;

UniformDescription POSTOCOORD("uPosToCoord");
UniformDescription ITERATION("uIteration");
UniformDescription ZVALUES("uZvalues");

GLfloat iter = 0;


void setupGradient(){
	Image::gradient gradient;
	gradient.push_back(Image::gradvector(0,glm::vec4(0,0,0.4,1)));
	gradient.push_back(Image::gradvector(1,glm::vec4(1,1,1,1)));
	color = Texture1D::create()->initialize(Image::fromGradient(512,gradient));
	color->setWrappingS(GL_CLAMP_TO_EDGE);
}

void setupVertexArray(){
	fullwindow_rect = VertexArray::generateVertexArray();
	position = ArrayBuffer::create()->initialize(pos,6,2,GL_FLOAT,GL_STATIC_DRAW);
	texCoord = ArrayBuffer::create()->initialize(tex,6,2,GL_FLOAT,GL_STATIC_DRAW);

	fullwindow_rect->add(AttributeDescription::POSITION,position);
	fullwindow_rect->add(AttributeDescription::TEXTURE_COORD_1,texCoord);


	fullwindow_rect->initialize(6);
}

void setupProgram() {
	calculator = ShaderProgram::fromPath("./simple2Dtex.vs","./mandelbrotcalc.fs");
	viewer = ShaderProgram::fromPath("./simple2Dtex.vs","./mandelbrotview.fs");

	calculator->initialize();
	viewer->initialize();

//	calculator->printActiveVariables(cout);
//	viewer->printActiveVariables(cout);

}

void print(const glm::vec4 & a ) {
	cout << "["<< a.x << ", " << a.y << ", " << a.z << ", " << a.w << "]"<< endl;
}


void setupGL() {
	OpenGLContext::initialize();
	OpenGLContext::SCREEN->initialize(screen_size);
	OpenGLContext::loadStandardVariableDescription();
	OpenGLContext::load(ITERATION);
	OpenGLContext::load(ZVALUES);
	OpenGLContext::load(POSTOCOORD);

	OpenGLContext::printspecs(cout);
	try {

		offscreen = Framebuffer::generateFramebuffer();
		offscreen->initialize(texture_size);

		for(int i = 0; i < 2 ; i++) {
			zValues[i] = Texture2D::create()->initialize(texture_size->width,texture_size->height);
			zValues[i]->setMagnifyMethod(GL_NEAREST);
			zValues[i]->setMinimizeMethod(GL_NEAREST);
			zValues[i]->setWrappingS(GL_CLAMP_TO_EDGE);
			zValues[i]->setWrappingT(GL_CLAMP_TO_EDGE);
			offscreen->attach(0,zValues[i]);
			offscreen->clearColor(glm::vec4(0,0,0,1));
		}

		setupVertexArray();
		setupGradient();
		setupProgram();

		fullwindow_rect->validate();
		OpenGLContext::checkForErrors();
	} catch (const Exception & e) {
		cout << e << endl;
		exit(-1);
	}

}

void updateTextures(const glm::mat4 & tranlation, const glm::mat4 & scale){
	tmatrix.translate = tranlation;
	tmatrix.scale = glm::scale(scale,glm::vec3(2,2,2));;
	tmatrix.F_matrix = s2t * glm::inverse(tmatrix.translate * tmatrix.scale);

	calculator->attachUniform(UniformDescription::MVP_MATRIX,tmatrix.translate * tmatrix.scale);

	calculator->attachUniform(POSTOCOORD,tmatrix.F_matrix);
	viewer->attachUniform(POSTOCOORD,tmatrix.F_matrix);
}

void updateScreen(const glm::mat4 & tranlation, const glm::mat4 & scale, const glm::mat4 & aspect){
	smatrix.scale = scale;
	smatrix.translate = tranlation;
	smatrix.aspect = aspect;
	viewer->attachUniform(UniformDescription::MVP_MATRIX, smatrix.translate * smatrix.scale * smatrix.aspect );
}

void restart(){
	for(int i = 0; i < 2 ; i++) {
		offscreen->attach(0,zValues[i]);
		offscreen->clearColor(glm::vec4(0,0,0,1));
	}
	iter = 0;
	updateTextures(smatrix.translate,smatrix.scale);
}



void GLFWCALL buttonCallback(int key, int action) {
	if(action != GLFW_RELEASE) return;

	int x, y;
	glfwGetMousePos(&x,&y);
	glm::vec3 mouse = glm::vec3(smatrix.translate * smatrix.scale * smatrix.aspect * glm::vec4(float(x)/screen_size->width*2 - 1, -float(y)/screen_size->height*2 + 1,0,1));

	glm::mat4 scale;
	if(key == 0) scale = glm::scale(smatrix.scale,glm::vec3(0.5f,0.5f,0.5f));
	else scale = glm::scale(smatrix.scale,glm::vec3(2,2,2));

	updateScreen(glm::translate(glm::mat4(),mouse),scale,smatrix.aspect);
}

int GLFWCALL closeCallback() {
	glfwTerminate();
	exit( EXIT_SUCCESS);
}

void GLFWCALL windowCallback(int width, int height) {
	delete screen_size;
	screen_size = new Area(0,0,width,height);
	OpenGLContext::SCREEN->setViewport(screen_size);

	updateScreen(smatrix.translate,smatrix.scale, glm::scale(glm::mat4(),glm::vec3( float(width) / height ,1,1)));
}

int main(){
	if(!glfwInit()){ exit( EXIT_FAILURE);}

	    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR,3);
	    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR,2);

	    if( !glfwOpenWindow( 800,600, 0,0,0,0,0,0, GLFW_WINDOW ) ) {
	         glfwTerminate();
	         exit( EXIT_FAILURE );
	     }

	    setupGL();

	    glfwSetWindowTitle("Mandelbrot step test");

	    updateScreen(glm::mat4(),glm::mat4(),glm::mat4());
        windowCallback(800,600);

        viewer->attachUniform(UniformDescription::COLOR_TEXTURE,color);
	    restart();

	    glfwSetMouseButtonCallback(&buttonCallback);
	    glfwSetWindowSizeCallback(&windowCallback);
	    glfwSetWindowCloseCallback(&closeCallback);
	    int d = 0, r = 1;

	    while(true){
	    	if (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS) {
	    	      break;
	    	} else if(glfwGetKey(GLFW_KEY_ENTER) == GLFW_PRESS) {
				restart();
	    	}
	    	if(iter > -1) {
	    		iter += 1;

	    		offscreen->attach(0,zValues[d]);
	    		calculator->attachUniform(ZVALUES,zValues[r]);

	    		OpenGLContext::draw(offscreen,calculator,fullwindow_rect);
	    		glDrawArrays(GL_TRIANGLES,0,6);
	    	}

	    	viewer->attachUniform(ZVALUES,zValues[d]);
	    	viewer->attachUniform(ITERATION,iter);
	    	OpenGLContext::draw(OpenGLContext::SCREEN,calculator,fullwindow_rect);
	    	glDrawArrays(GL_TRIANGLES,0,6);

	    	d = d ? 0 : 1;
	    	r = r ? 0 : 1;

	    	glfwSwapBuffers();
	    }

	    glfwTerminate();
	    return 1;
}
