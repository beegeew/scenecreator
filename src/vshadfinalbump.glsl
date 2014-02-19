#version 330 core

layout(location = 0) in vec3 vPosition;
layout(location = 2) in vec2 vertexUV;
layout(location = 1) in vec3 vNorm;
layout(location = 3) in vec3 vTangent;
layout(location = 4) in vec3 vBitangent;

out vec2 UV;
out vec3 N;
out vec3 E,Et;
out vec3 L0,L0t;
out vec3 L1,L1t;
out vec3 L2,L2t;
out vec3 L3,L3t;
out vec3 L4,L4t;
out vec3 L5,L5t;
out vec3 L6,L6t;
out vec3 L7,L7t;
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
uniform vec3 MV3x3;

void main() 
{
	gl_Position = P*MV*vec4(vPosition,1.0);
	vec3 pos = (M*vec4(vPosition,1.0)).xyz;
	 
	 vec3 vertexPos = (V*M*vec4(vPosition,1)).xyz;
	E = vec3(0,0,0) - vertexPos;
	N = (V*M*vec4(vNorm,0.0)).xyz;
	
	vec3 vTanCam = MV3x3 * vTangent;
	vec3 vBitanCam = MV3x3 * vBitangent;
	vec3 vNormCam = MV3x3 * vNorm;
	
	mat3 TBN = transpose(mat3(vTanCam, vBitanCam, vNormCam));
	Et = TBN * E;
	 
	if (numLights > 0) {
		vec3 lPosCam = (V*M*vec4(lightPos0.xyz,1.0)).xyz;
		L0 = lPosCam + E;
		L0t = TBN * L0;
	}
	
	if (numLights > 1) {
		vec3 lPosCam = (V*vec4(lightPos1.xyz,1.0)).xyz;
		L1 = lPosCam + E;
		L1t = TBN * L1;
	}
	
	if (numLights > 2) {
		vec3 lPosCam = (V*vec4(lightPos2.xyz,1.0)).xyz;
		L2 = lPosCam + E;
		L2t = TBN * L2;
	}
	
	if (numLights > 3) {
		vec3 lPosCam = (V*vec4(lightPos3.xyz,1.0)).xyz;
		L3 = lPosCam + E;
		L3t = TBN * L3;
	}
	
	if (numLights > 4) {
		vec3 lPosCam = (V*vec4(lightPos4.xyz,1.0)).xyz;
		L4 = lPosCam + E;
		L4t = TBN * L4;
	}
	
	if (numLights > 5) {
		vec3 lPosCam = (V*vec4(lightPos5.xyz,1.0)).xyz;
		L5 = lPosCam + E;
		L5t = TBN * L5;
	}
	
	if (numLights > 6) {
		vec3 lPosCam = (V*vec4(lightPos6.xyz,1.0)).xyz;
		L6 = lPosCam + E;
		L6t = TBN * L6;
	}
	
	if (numLights > 7) {
		vec3 lPosCam = (V*vec4(lightPos7.xyz,1.0)).xyz;
		L7 = lPosCam + E;
		L7t = TBN * L7;
	}
	 
	UV = vertexUV;
}
