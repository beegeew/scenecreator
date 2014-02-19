#ifndef OGLOBJ_H
#define OGLOBJ_H

#define MAX_LIGHTS 8

#include <GL/glew.h>
#include <GL/glfw.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <String>
#include "controls.h"
#include "textload.h"
#include "objloader.h"
#include "initshader.h"
#include "structs.h"
#include "tangentcalc.h"

class oglobj
{
public:
	oglobj();
	oglobj(string inOBJ, modelProp inMat, string inText = "");
	~oglobj(void);

	void init(); //read objfile and setup all needed arrays
	void render();//send everything to the shaders
	
	void setView(glm::mat4 inView) {myView = inView;}
	glm::mat4 getView() {return myView;}
	void setModel(glm::mat4 inModel) {model = inModel;}
	glm::mat4 getModel() {return model;}
	void setModelV(glm:: mat4 inMV) {mv = inMV;}
	glm::mat4 getModelV() {return mv;} //only called by self and children - parents render first
	void setProj(glm::mat4 inProj) {myProj = inProj;}
	glm::mat4 getProj() {return myProj;} //only called by self and children - parents render first

	bool hasChildren() { return (children.size() > 0 ? true : false);}
	vector<int> children;
	
	void setPos(vec3 inPos) {pos = inPos; currPos = inPos;}
	void setScale(vec3 inScale) {scale = inScale;}
	void setType(string inType) {type = inType;}
	string getType() {return type;}
	void addLight(lightProp newLight) {lights.push_back(newLight);}
	void addChild(int childNum) { children.push_back(childNum);}
	bool hasText() { return text;}
	void setParent(int newPar) {parent = newPar;}
	int getParent() {return parent;}
	void setBumpMap(string inName);
	void setStaticRot(vec3 inRot);
	void setRot(char inAxis) { axis = inAxis; rot = true;}
	void setPath(char inPathDir, float inDist) {hasPath = toSecond = true; pathDir = inPathDir; dist = inDist; }
	void setAlpha(float inAlpha) {alpha = inAlpha; isBlend = true;}

private:
	bool text, rot,dim, addOffset,addPosOffset, hasBump, hasStatRot;
	bool hasPath, toSecond, isBlend;
	string type, textureFile, objectFile, bumpMap, fShad,vShad;
	int parent;
	char axis, pathDir;

	glm::mat4 mv, model;
	glm::mat4 myProj, myView;

	vec3 pos, scale,thetaStatic, thetaActive, currPos, color;
	float rotSpeed, currTextOffset, posOffset, alpha;
	float brightnessFac, rotStatic, dist;

	GLuint MVP, trans, vVertID, vNormID, vTextID, vArray;
	GLuint vertexbuffer, uvbuffer, normalbuffer, bitanbuffer, tanbuffer;
	GLuint program, vPosition, myText, myTextID, myNormID;
	GLuint lightID, vRotID, lightColID,myText2,myText2ID, myBump, myBumpMapID;

	modelProp mat;
	vector<lightProp> lights;

	vector<glm::vec3> vVerts;
	vector<glm::vec3> vNorms;
	vector<glm::vec2> vTexts;
	vector<glm::vec3> vBitans;
	vector<glm::vec3> vTans;
};

#endif
