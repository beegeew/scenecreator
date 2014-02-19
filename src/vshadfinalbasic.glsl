#version 330 core

layout(location = 0) in vec3 vPosition;
layout(location = 2) in vec2 vertexUV;

out vec2 UV;

uniform mat4 MV;
uniform mat4 V;
uniform mat4 M;
uniform mat4 P;

void main()
{
	gl_Position = P*MV*vec4(vPosition,1.0f);
	
	UV = vertexUV;
}