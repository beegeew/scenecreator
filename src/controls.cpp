//My custom keyboard/mouse functions
//constructed with help from opengl-tutorial.org

#include "controls.h"
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
#include "structs.h"

using namespace glm;

//globals - we always need to know these
glm::mat4 view;
glm::mat4 proj;

//returns projection matrix as calculated from keyboard/mouse movements
glm::mat4 getProjMat() {	return proj;}

//returns view matrix as calculated from keyboard/mouse movements
glm::mat4 getViewMat() {	return view;}

//Variables that we want to always keep track of (more globals yes, but not the matrices)
glm::vec3 pos = glm::vec3(0,0,3);
glm::vec3 at = glm::vec3(0,0,0);
glm::vec3 up = glm::vec3(0,1,0);
float fovy = 35.0f, zNear = 0.1f, zFar = 100.0f, speedMov = 0.02f;
glm::vec3 theta = vec3(0.0f,0.0f,0.0f);
float leftL = -2, rightL = 2, top = 2, bottom = -2;
char type = 'p';
char dir = 'y';

void setCam(cameraProp incProp) {
	if (incProp.type == 'o')
	{
		type = 'o'; zNear = incProp.zne; zFar = incProp.zfa;
		top = incProp.top; bottom = incProp.bot; leftL = incProp.left; rightL = incProp.right;
	} else if (incProp.type == 'p') {
		type = 'p'; fovy = incProp.fov; zNear = incProp.zne; zFar = incProp.zfa;
	}
	pos = incProp.eye; at = incProp.at; up = incProp.up;
}
//triggered on keyboard/mouse movements
void computeMat() 
{	
	int currWidth, currHeight;
	glfwGetWindowSize(&currWidth, &currHeight);

	static std::string inFile;
	//capture WASD keypresses and respond appropriately
	if(glfwGetKey('W') == GLFW_PRESS) {fovy -= speedMov;}
	if(glfwGetKey('S') == GLFW_PRESS) {fovy += speedMov;}
	if(glfwGetKey('D') == GLFW_PRESS) {theta.y-=.1f; if (theta.y < 0) theta.y+=360.0f; dir = 'y';}
	if(glfwGetKey('A') == GLFW_PRESS) {theta.y+=.1f; if (theta.y > 360) theta.y-=360.0f; dir = 'y';}
	if(glfwGetKey('P') == GLFW_PRESS) {speedMov -= 0.0001f; if (speedMov < 0) speedMov = 0.0f;}
	if(glfwGetKey('O') == GLFW_PRESS) {speedMov += 0.0001f;}
	if(glfwGetKey('Q') == GLFW_PRESS) {theta.x-=.1f; if (theta.x < 0) theta.x+=360.0f; dir = 'x';}
	if(glfwGetKey('E') == GLFW_PRESS) {theta.x+=.1f; if (theta.x > 360) theta.x-=360.0f; dir = 'x';}
	if(glfwGetKey('Z') == GLFW_PRESS) {theta.z-=.1f; if (theta.z < 0) theta.z+=360.0f; dir = 'z';}
	if(glfwGetKey('X') == GLFW_PRESS) {theta.z+=.1f; if (theta.z > 360) theta.z-=360.0f; dir = 'z';}
	if(glfwGetMouseButton(GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) {
		std::cout <<"Input a new scene file name\n"; std::cin >> inFile; 
	}

	//Finally set the projection matrix!
	if (type == 'p')
		proj = glm::perspective(fovy,float(currWidth/currHeight),zNear,zFar);
	else if (type == 'o')
		proj = glm::ortho(leftL, rightL, bottom, top, zNear, zFar);

	view = glm::lookAt(pos,at,up);

	view = glm::rotate(view,theta.x,glm::vec3(1.0f,0.0f,0.0f));
	view = glm::rotate(view,theta.y,glm::vec3(0.0f,1.0f,0.0f));
	view = glm::rotate(view,theta.z,glm::vec3(0.0f,0.0f,1.0f));
}
