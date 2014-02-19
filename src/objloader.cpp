//my obj loader - written with help of my brain
//weeeee
//Models are typically from blender and stuff I find which is triangulated and has vt & vn ideal for Opengl 3+ core
//

#include "objloader.h"

using namespace std;
using namespace glm;

bool loadOBJ(const char* file, vector<glm::vec3> &outVs, vector<glm::vec2> &outVts, vector<glm::vec3> &outVns)
{
	//Attempt to open file - check if open
	ifstream objFile;
	objFile.open(file);

	if(!objFile) {printf("OBJ file %s failed to open, exiting parser\n",file); return false;}

	//OutVs - vertices going out	outVts - texture positions going out	outVns - normals going out
	string inLine, token;
	vector<vec3> tempVerts, tempNorms;
	vector<vec2> tempTexts;
	int face[9];
	stringstream ss;

	while(!objFile.eof()) {
		getline(objFile,inLine);
		ss.str(inLine);
		while (ss >> token) {
			if (token == "v") {
				glm::vec3 vert;
				ss >> token; vert.x = atof(token.c_str());ss >> token; vert.y = atof(token.c_str());ss >> token; vert.z = atof(token.c_str());
				tempVerts.push_back(vert);
			} else if (token == "vn") {
				glm::vec3 norm;
				ss >> token; norm.x = atof(token.c_str());ss >> token; norm.y = atof(token.c_str());ss >> token; norm.z = atof(token.c_str());
				tempNorms.push_back(norm);
			} else if (token == "vt") {
				glm::vec2 text;
				ss >> token; text.x = atof(token.c_str());ss >> token; text.y = atof(token.c_str());
				tempTexts.push_back(text);
			} else if (token == "f") {
				if (tempVerts.size() == 0 || tempNorms.size() == 0) {
					printf("OBJ file format is missing vertex and/or normal data - cannot continue building model\n");
					return false;
				} else if (tempTexts.size() == 0) {
					ss >> token; sscanf(token.c_str(),"%d//%d",&face[0],&face[3]); //extract point/texture/normal
					ss >> token; sscanf(token.c_str(),"%d//%d",&face[1],&face[4]);
					ss >> token; sscanf(token.c_str(),"%d//%d",&face[2],&face[5]);
					outVs.push_back(tempVerts[face[0]-1]); outVns.push_back(tempNorms[face[3]-1]);
					outVs.push_back(tempVerts[face[1]-1]); outVns.push_back(tempNorms[face[4]-1]);
					outVs.push_back(tempVerts[face[2]-1]); outVns.push_back(tempNorms[face[5]-1]);
				} else {
					ss >> token; sscanf(token.c_str(),"%d/%d/%d",&face[0],&face[6],&face[3]); //extract point/texture/normal
					ss >> token; sscanf(token.c_str(),"%d/%d/%d",&face[1],&face[7],&face[4]);
					ss >> token; sscanf(token.c_str(),"%d/%d/%d",&face[2],&face[8],&face[5]);
					outVs.push_back(tempVerts[face[0]-1]); outVns.push_back(tempNorms[face[3]-1]); outVts.push_back(tempTexts[face[6]-1]);
					outVs.push_back(tempVerts[face[1]-1]); outVns.push_back(tempNorms[face[4]-1]); outVts.push_back(tempTexts[face[7]-1]);
					outVs.push_back(tempVerts[face[2]-1]); outVns.push_back(tempNorms[face[5]-1]); outVts.push_back(tempTexts[face[8]-1]);
				}
			}	
		}
		ss.clear();
	}

	objFile.close();
	return true;
}
