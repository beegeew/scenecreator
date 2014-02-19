//My custom keyboard/mouse functions
//constructed with help from opengl-tutorial.org

#ifndef _CONTROLS_H
#define _CONTROLS_H

#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "structs.h"

using namespace glm;

void computeMat();

glm::mat4 getProjMat();
glm::mat4 getViewMat();
void setCam(cameraProp incProp);

#endif
