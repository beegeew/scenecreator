#ifndef _STRUCTS_H
#define _STRUCTS_H

#include <glm/glm.hpp>
using namespace glm;

struct modelProp {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shine;
};

struct lightProp {
	vec3 col;
	vec4 pos;
	char type;
};

struct cameraProp {
	char type;
	float fov;
	float zne;
	float zfa;
	float asp;
	vec3 eye;
	vec3 at;
	vec3 up;
	float top;
	float bot;
	float left;
	float right;
};

#endif
