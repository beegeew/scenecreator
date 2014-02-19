//my obj loader - written with help of my brain
//weeeee
//Models are typically from blender also stuff I find on my own
//

#ifndef _OBJLOADER_H
#define _OBJLOADER_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <glm/glm.hpp>
#include <vector>

using namespace glm;
using namespace std;

bool loadOBJ(const char* file, vector<glm::vec3> &outVert, vector<glm::vec2> &outVt, vector<glm::vec3> &outVn);

#endif
