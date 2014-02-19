#version 330 core

uniform vec3 lightCol0;
uniform vec3 lightCol1;
uniform vec3 lightCol2;
uniform vec3 lightCol3;
uniform vec3 lightCol4;
uniform vec3 lightCol5;
uniform vec3 lightCol6;
uniform vec3 lightCol7;

uniform vec4 lightPos0;
uniform vec4 lightPos1;
uniform vec4 lightPos2;
uniform vec4 lightPos3;
uniform vec4 lightPos4;
uniform vec4 lightPos5;
uniform vec4 lightPos6;
uniform vec4 lightPos7;
uniform float matShi;
uniform vec3 matAmb;
uniform vec3 matSpec;
uniform mat3 MV3x3;
uniform mat4 V;
uniform mat4 M;

uniform int numLights;

in vec2 UV;
in vec3 N;
in vec3 E,Et;
in vec3 L0,L0t;
in vec3 L1,L1t;
in vec3 L2,L2t;
in vec3 L3,L3t;
in vec3 L4,L4t;
in vec3 L5,L5t;
in vec3 L6,L6t;
in vec3 L7,L7t;
in vec3 pos;

out vec3 color;

uniform sampler2D myTexture;
uniform sampler2D myBump;
//uniform sampler2D myTexture2;

void main() 
{	
	vec3 matDiff = texture2D(myTexture,UV).rgb;
	//*offset+ texture2D(myTexture2,UV).rgb*(1-offset);
	vec3 mA = matAmb*matDiff;
	
	vec3 NN = normalize(texture2D(myBump,UV).rgb*2.0-1.0);

	vec3 EE = normalize(E);

	vec3 tempColor;
	
	if (numLights > 0 ) {
		float dist = length(lightPos0.xyz - pos);
		if (lightPos1.w == 0.0) dist = 1.0f;
		if (dist < 1.0) dist = 1.0f;
		vec3 LL = normalize(L0);
		float cosTheta = clamp(dot(NN,LL),0,1);
		vec3 R = reflect(-LL,NN);
		float cosAlpha = clamp(dot(EE,R),0,1);
		tempColor = matDiff*lightCol0*cosTheta/(dist*dist)+matSpec*lightCol0*pow(cosAlpha,5)/(dist*dist);
	}
	
	if (numLights > 1 ) {
		float dist = length(lightPos1.xyz - pos);
		if (lightPos1.w == 0.0) dist = 1.0f;
		if (dist < 1.0) dist = 1.0f;
		vec3 LL = normalize(L1);
		float cosTheta = clamp(dot(NN,LL),0,1);
		vec3 R = reflect(-LL,NN);
		float cosAlpha = clamp(dot(EE,R),0,1);
		tempColor += matDiff*lightCol1*cosTheta/(dist*dist)+matSpec*lightCol1*pow(cosAlpha,5)/(dist*dist);
	}
	
	if (numLights > 2 ) {
		float dist = length(lightPos2.xyz - pos);
		if (lightPos2.w == 0.0) dist = 1.0f;
		vec3 LL = normalize(L2);
		float cosTheta = clamp(dot(NN,LL),0,1);
		vec3 R = reflect(-LL,NN);
		float cosAlpha = clamp(dot(EE,R),0,1);
		tempColor += matDiff*lightCol2*cosTheta/(dist*dist)+matSpec*lightCol2*pow(cosAlpha,5)/(dist*dist);
	}
	
	if (numLights > 3 ) {
		float dist = length(lightPos3.xyz - pos);
		if (lightPos3.w == 0.0) dist = 1.0f;
		vec3 LL = normalize(L3);
		float cosTheta = clamp(dot(NN,LL),0,1);
		vec3 R = reflect(-LL,NN);
		float cosAlpha = clamp(dot(EE,R),0,1);
		tempColor += matDiff*lightCol3*cosTheta/(dist*dist)+matSpec*lightCol3*pow(cosAlpha,5)/(dist*dist);
	}
	
	if (numLights > 4 ) {
		float dist = length(lightPos4.xyz - pos);
		if (lightPos4.w == 0.0) dist = 1.0f;
		vec3 LL = normalize(L4);
		float cosTheta = clamp(dot(NN,LL),0,1);
		vec3 R = reflect(-LL,NN);
		float cosAlpha = clamp(dot(EE,R),0,1);
		tempColor += matDiff*lightCol4*cosTheta/(dist*dist)+matSpec*lightCol4*pow(cosAlpha,5)/(dist*dist);
	}
	
	if (numLights > 5 ) {
		float dist = length(lightPos5.xyz - pos);
		if (lightPos5.w == 0.0) dist = 1.0f;
		vec3 LL = normalize(L5);
		float cosTheta = clamp(dot(NN,LL),0,1);
		vec3 R = reflect(-LL,NN);
		float cosAlpha = clamp(dot(EE,R),0,1);
		tempColor += matDiff*lightCol5*cosTheta/(dist*dist)+matSpec*lightCol5*pow(cosAlpha,5)/(dist*dist);
	}
	
	if (numLights > 6 ) {
		float dist = length(lightPos6.xyz - pos);
		if (lightPos6.w == 0.0) dist = 1.0f;
		vec3 LL = normalize(L6);
		float cosTheta = clamp(dot(NN,LL),0,1);
		vec3 R = reflect(-LL,NN);
		float cosAlpha = clamp(dot(EE,R),0,1);
		tempColor += matDiff*lightCol6*cosTheta/(dist*dist)+matSpec*lightCol6*pow(cosAlpha,5)/(dist*dist);
	}
	
	if (numLights > 7 ) {
		float dist = length(lightPos7.xyz - pos);
		if (lightPos7.w == 0.0) dist = 1.0f;
		vec3 LL = normalize(L7);
		float cosTheta = clamp(dot(NN,LL),0,1);
		vec3 R = reflect(-LL,NN);
		float cosAlpha = clamp(dot(E,R),0,1);
		tempColor += matDiff*lightCol7*cosTheta/(dist*dist)+matSpec*lightCol7*pow(cosAlpha,5)/(dist*dist);
	}
	
	//color = NN;
	color = mA + tempColor;
	//color = vec3(1.0f,0.0f,0.0f);
}
