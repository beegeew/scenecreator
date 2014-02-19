//Project 4 take 2 since the first time with Angel was a bust
//Ugh
//Beverly Wertz

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <GL/glew.h>
#include <GL/glfw.h>

//glmathematics - multiplatform opengl math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

//stuff that might be used more than once - my functions
#include "initshader.h"
#include "textload.h"
#include "controls.h"
#include "objloader.h"
#include "oglobj.h"
#include "scene.h"

using namespace std;
scene *myScene;

int main(int argc, char* argv[]) 
{
	//Init GLFW
	if ( !glfwInit() ) {
		fprintf(stderr, "GLFW did not initialize\n");
		return -1;
	}

	glfwOpenWindowHint(GLFW_FSAA_SAMPLES,4);
	//Only Core functionalities here, none of that silly 2.x and lower stuff! (This ensures 3.2 compliant - my old video card won't support 4 :( )
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR,3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR,2);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if ( !glfwOpenWindow(512,512,0,0,0,0,32,0,GLFW_WINDOW)) {
		fprintf(stderr, "GLFW window open failed!\n");
		glfwTerminate();
		return -1;
	}

	//Now that GLFW is up and running - lets think about glew
	if ( glewInit()!=GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	glfwSetWindowTitle("Beverly G Wertz - Final Project - Child's Play");

	//Should be a dark purple background
	glClearColor(.2f,0.0f,0.2f,1.0f);
	glfwEnable(GLFW_STICKY_KEYS);
	int width, height;
	glfwGetWindowSize(&width, &height);
	glfwSetMousePos(width/2,height/2);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); 
	glEnable(GL_CULL_FACE);

	

	//create a new scene
	myScene = new scene("scene1.txt");
	myScene->readFile();

	do{
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		computeMat();

		myScene->render();

        // Swap buffers
        glfwSwapBuffers();
	} while(glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS && glfwGetWindowParam(GLFW_OPENED));
	
	glfwTerminate();

	return 0;
}