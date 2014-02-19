//This is my scene parser and manager! 

#ifndef _SCENE_H
#define _SCENE_H

#include <sstream>
#include <String>
#include <fstream>
#include <vector>
#include <stack>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "controls.h"
#include "structs.h"

using namespace glm;
using namespace std;

class scene
{
public:
	scene(string inScene = "scene1.txt");
	~scene(void);

	bool readFile();
	void render();

	void init();
	void changeFIle(string inFile);
	void readLight(istream& in, string inLine);
	void readCam(istream& in, string inLine);
	void readObj(istream& in, string inLine);
	void readNode(istream& in, string inLine);
	bool find(string token);

private:
	vector<oglobj> myScene;
	vector<oglobj> tempObj; //prototype objects from when we read in the scene file

	string sceneFile;

	vector<lightProp> lights;
	stack<glm::mat4> mvStack;
};

#endif
