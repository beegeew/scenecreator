#version 330 core

layout(location = 0) in vec3 vPosition;
layout(location = 2) in vec2 vertexUV;
layout(location = 1) in vec3 vNorm;

out vec2 UV;
out vec3 N;
out vec3 E;
out vec3 L0;
out vec3 L1;
out vec3 L2;
out vec3 L3;
out vec3 L4;
out vec3 L5;
out vec3 L6;
out vec3 L7;
out vec3 pos;

uniform mat4 MV;
uniform mat4 V;
uniform mat4 M;
uniform mat4 P;

uniform vec4 lightPos0;
uniform vec4 lightPos1;
uniform vec4 lightPos2;
uniform vec4 lightPos3;
uniform vec4 lightPos4;
uniform vec4 lightPos5;
uniform vec4 lightPos6;
uniform vec4 lightPos7;
uniform int numLights;

void main() 
{
	gl_Position = P*MV*vec4(vPosition,1.0);
	vec3 pos = (M*vec4(vPosition,1.0)).xyz;
	 
	 vec3 vertexPos = (V*M*vec4(vPosition,1)).xyz;
	E = vec3(0,0,0) - vertexPos;
	N = (V*M*vec4(vNorm,0.0)).xyz;
	 
	if (numLights > 0) {
		vec3 lPosCam = (V*vec4(lightPos0.xyz,1.0)).xyz;
		L0 = lPosCam + E;
	}
	
	if (numLights > 1) {
		vec3 lPosCam = (V*vec4(lightPos1.xyz,1.0)).xyz;
		L1 = lPosCam + E;
	}
	
	if (numLights > 2) {
		vec3 lPosCam = (V*vec4(lightPos2.xyz,1.0)).xyz;
		L2 = lPosCam + E;
	}
	
	if (numLights > 3) {
		vec3 lPosCam = (V*vec4(lightPos3.xyz,1.0)).xyz;
		L3 = lPosCam + E;
	}
	
	if (numLights > 4) {
		vec3 lPosCam = (V*vec4(lightPos4.xyz,1.0)).xyz;
		L4 = lPosCam + E;
	}
	
	if (numLights > 5) {
		vec3 lPosCam = (V*vec4(lightPos5.xyz,1.0)).xyz;
		L5 = lPosCam + E;
	}
	
	if (numLights > 6) {
		vec3 lPosCam = (V*vec4(lightPos6.xyz,1.0)).xyz;
		L6 = lPosCam + E;
	}
	
	if (numLights > 7) {
		vec3 lPosCam = (V*vec4(lightPos7.xyz,1.0)).xyz;
		L7 = lPosCam + E;
	}
	 
	UV = vertexUV;
}
