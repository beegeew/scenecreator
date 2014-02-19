#include "oglobj.h"
#include "scene.h"
#include "structs.h"
#include "controls.h"

scene::scene(string inScene)
{
	sceneFile = inScene;
}

void scene::init()
{
	for (int i = 0; i < myScene.size(); i++) {
		myScene[i].init();
	}
}

void scene::render()
{
	glm::mat4 tempV, tempProj;
	int tempParent;
	for (int i = 0; i < myScene.size(); i++) {
		tempParent = myScene[i].getParent();
		//Check parent - set to 0 if invalid
		if (tempParent >= myScene.size())
			tempParent = 0;
		if (tempParent != -1) {
			myScene[i].setView(myScene[tempParent].getView());
			myScene[i].setProj(myScene[tempParent].getProj());
			myScene[i].setModel(myScene[tempParent].getModel());
		}
		myScene[i].render();
	}
}

bool scene::readFile()
{
	ifstream in;
	in.open(sceneFile);

	if(!in) {
		printf("%s: would not open, please try another file\n",sceneFile.c_str());
		return false;
	}

	string inLine, token;
	stringstream ss;

	while ( !in.eof())
	{
		getline(in,inLine);
		if (inLine.length() > 0) {
			switch(tolower(inLine[0])) {
			case 'l':
				readLight(in,inLine); break;
			case 'p':
				readCam(in,inLine); break;
			case 'n':
				readNode(in,inLine); break;
			case 'o':
				readObj(in,inLine); break;
			case '#':
			default:
				break;
			}
		}
	}

	if (myScene.size() > 0)
		init();

	return true;
}

void scene::readLight(istream& in, string inLine) 
{
	if (lights.size() == MAX_LIGHTS) {
		printf("Maximum lights %d already specified. Ignoring this light.\n");
		return;
	}

	lightProp tempProp;
	tempProp.col = vec3(1.0,1.0,1.0);
	tempProp.pos = vec4(4.0f,4.0f,4.0f,0.0f);
	tempProp.type = 'd';

	stringstream ss;
	ss.str(inLine);

	bool more = true;
	string token, newLine;

	while(more) {
		while (ss >> token) {
			if (token == "}")
				more = false;
			else if(token == "col") {
				ss >> token; tempProp.col.x = atof(token.c_str());
				ss >> token; tempProp.col.y = atof(token.c_str());
				ss >> token; tempProp.col.z = atof(token.c_str());
			} else if (token == "pos") {
				ss >> token; tempProp.pos.x = atof(token.c_str());
				ss >> token; tempProp.pos.y = atof(token.c_str());
				ss >> token; tempProp.pos.z = atof(token.c_str());
			} else if (token == "type") {
				ss >> token;
				if (token == "dir") tempProp.pos.w = 0.0f;
				else if (token == "point") tempProp.pos.w = 1.0f;
			}
		}
		if(more) {
			getline(in,newLine);
			ss.clear();
			ss.str(newLine);
		}
	}

	lights.push_back(tempProp);
}

void scene::readCam(istream& in, string inLine) 
{
	cameraProp tempProp;
	tempProp.fov = 45; tempProp.left = tempProp.right = tempProp.top = tempProp.bot;
	tempProp.asp = 1; tempProp.zfa = 100.0f; tempProp.zne = 0.1; tempProp.eye = vec3(3.0,3.0,3.0);
	tempProp.at = vec3(0.0,0.0,0.0); tempProp.up = vec3(0.0,1.0,0.0);
	tempProp.type = 'p';

	stringstream ss;
	ss.str(inLine);

	bool more = true;
	string token, newLine;

	while(more) {
		while (ss >> token) {
			if (token == "}")
				more = false;
			else if(token == "eye") {
				ss >> token; tempProp.eye.x = atof(token.c_str());
				ss >> token; tempProp.eye.y = atof(token.c_str());
				ss >> token; tempProp.eye.z = atof(token.c_str());
			} else if ( token == "at") {
				ss >> token; tempProp.at.x = atof(token.c_str());
				ss >> token; tempProp.at.y = atof(token.c_str());
				ss >> token; tempProp.at.z = atof(token.c_str());
			} else if ( token == "up") {
				ss >> token; tempProp.up.x = atof(token.c_str());
				ss >> token; tempProp.up.y = atof(token.c_str());
				ss >> token; tempProp.up.z = atof(token.c_str());
			} else if (token == "top") {
				ss >> token; tempProp.top = atof(token.c_str());
			} else if (token == "bot") {
				ss >> token; tempProp.bot = atof(token.c_str());
			} else if (token == "lef") {
				ss >> token; tempProp.left = atof(token.c_str());
			} else if (token == "rig") {
				ss >> token; tempProp.right = atof(token.c_str());
			} else if (token == "zne") {
				ss >> token; tempProp.zne = atof(token.c_str());
			} else if (token == "zfa") {
				ss >> token; tempProp.zfa = atof(token.c_str());
			} else if (token == "asp") {
				ss >> token; tempProp.asp = atof(token.c_str());
			} else if (token == "fov") {
				ss >> token; tempProp.fov = atof(token.c_str());
			} else if (token == "typ") {
				ss >> token; tempProp.type = token.c_str()[0];
			}
		}
		if(more) {
			getline(in,newLine);
			ss.clear();
			ss.str(newLine);
		}
	}

	setCam(tempProp);
}

void scene::readObj(istream& in, string inLine) 
{
	modelProp tempMat;
	string tempOBJname,tempTextName, objType, tempBump;

	stringstream ss;
	ss.str(inLine);

	bool more = true;
	string token, newLine;

	while(more) {
		while (ss >> token) {
			if (token == "}") more = false;
			else if (token == "nam") {
				ss >> token; objType = token;
			} else if(token == "amb") {
				ss >> token; tempMat.ambient.x = atof(token.c_str());
				ss >> token; tempMat.ambient.y = atof(token.c_str());
				ss >> token; tempMat.ambient.z = atof(token.c_str());
			} else if (token == "dif") {
				ss >> token; tempMat.diffuse.x = atof(token.c_str());
				ss >> token; tempMat.diffuse.y = atof(token.c_str());
				ss >> token; tempMat.diffuse.z = atof(token.c_str());
			} else if (token == "spe") {
				ss >> token; tempMat.specular.x = atof(token.c_str());
				ss >> token; tempMat.specular.y = atof(token.c_str());
				ss >> token; tempMat.specular.z = atof(token.c_str());
			} else if (token == "obj") {
				ss >> token; tempOBJname = token.c_str();
			} else if (token == "tex") {
				ss >> token; if (token == "-1") tempTextName = ""; else tempTextName = token;
			} else if (token == "shi") {
				ss >> token; tempMat.shine = atof(token.c_str());
			} else if (token == "bump") {
				ss >> token; tempBump = token;
			}
		}
		if(more) {
			getline(in,newLine);
			ss.clear();
			ss.str(newLine);
		}
	}

	oglobj tempOb(tempOBJname,tempMat,tempTextName);
	tempOb.setType(objType);
	if (tempBump.size() != 0) {tempOb.setBumpMap(tempBump);}

	tempObj.push_back(tempOb);
}

void scene::readNode(istream& in, string inLine)
{
	if (tempObj.empty()) {
		printf("Cannot build nodes with an empty object container. Please read the documentation and reformat your scene file.\n");
		return;
	}

	stringstream ss;
	ss.str(inLine);

	bool more = true, path = false, isBlend = false;
	string token, newLine;
	glm::vec3 pos = vec3(0.0f,0.0f,0.0f), scale = vec3(1.0f,1.0f,1.0f), rotStatic = vec3(0.0f,0.0f,0.0f);
	int parent = 0;
	string objType = "";
	char axis = 'n', axisPath = 'n';
	float rotSpeed = 0.0f, dist = 0.0f, inAlpha = 0.0f;

	while(more) {
		while (ss >> token) {
			if (token == "}") more = false;
			else if (token == "typ") {
				ss >> token; if (find(token)) objType = token;
			} else if(token == "pos") {
				ss >> token; pos.x = atof(token.c_str());
				ss >> token; pos.y = atof(token.c_str());
				ss >> token; pos.z = atof(token.c_str());
			} else if ( token == "scl") {
				ss >> token; scale.x = atof(token.c_str());
				ss >> token; scale.y = atof(token.c_str());
				ss >> token; scale.z = atof(token.c_str());
			} else if (token == "par") {
				ss >> token; parent = atoi(token.c_str());
			} else if (token == "path") {
				ss >> token; axisPath = token[0];
				ss >> token; dist = atof(token.c_str());
				if (axisPath == 'x' || axisPath == 'y' || axisPath == 'z')
					path = true;
			} else if (token == "rots") {
				ss >> token; rotStatic.x = atof(token.c_str());
				ss >> token; rotStatic.y = atof(token.c_str());
				ss >> token; rotStatic.z = atof(token.c_str());
			} else if (token == "rot") {
				ss >> token; axis = token[0];
			} else if (token == "blend") {
				ss >> token; inAlpha = atof(token.c_str()); isBlend = true;
			}
			if(more) {
				getline(in,newLine);
				ss.clear();
				ss.str(newLine);
			}
		}
	}

	for (int i = 0; i < tempObj.size(); i++) {
		if (tempObj[i].getType() == objType)	{
			myScene.push_back(tempObj[i]);
			for (int j = 0; j < lights.size(); j++)
				myScene[myScene.size()-1].addLight(lights[j]);
			myScene[myScene.size()-1].setPos(pos);
			myScene[myScene.size()-1].setScale(scale);
			myScene[myScene.size()-1].setStaticRot(rotStatic);
			if (axis == 'x' || axis == 'y' || axis == 'z')
				myScene[myScene.size()-1].setRot(axis);
			if (path)
				myScene[myScene.size()-1].setPath(axisPath,dist);
			if (isBlend)
				myScene[myScene.size()-1].setAlpha(inAlpha);
			if (parent == -1){
				myScene[myScene.size()-1].setParent(parent);
			} else if (parent < myScene.size()-1 && parent > -1) {
				myScene[myScene.size()-1].setParent(parent);
				myScene[parent].addChild(myScene.size()-1);
			} else {
				cout << "Parent selected is invalid, setting to main node.\n";
				myScene[myScene.size()-1].setParent(0);
				myScene[0].addChild(myScene.size()-1);
			}
			return;
		}
	}
}

void scene::changeFIle(string newFile)
{
	sceneFile = newFile;
	if (!readFile())
		sceneFile = "scene1.txt";
	readFile();
}

bool scene::find(string token)
{
	for (int i = 0; i < tempObj.size(); i++)
		if (tempObj[i].getType() == token) return true;

	return false;
}

scene::~scene(void)
{
}
