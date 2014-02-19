#include "oglobj.h"
#include "structs.h"

using namespace std;
using namespace glm;

oglobj::oglobj(string objFile, modelProp inMat, string inText)
{
	mat = inMat;
	textureFile = inText;
	objectFile = objFile;
	thetaActive = thetaStatic = currPos = vec3(0.0f,0.0f,0.0f);
	brightnessFac = .001;
	hasBump = dim = false;
	posOffset = currTextOffset = alpha = 0.0f;
	hasPath = toSecond = isBlend = false;
}

//setup VAO's and shaders, let's get ready to draw!
void oglobj::init()
{
	bool res = loadOBJ(objectFile.c_str(),vVerts, vTexts, vNorms);
	if (!res) {
		printf("Failed to read supplied OBJ file, reading a cube instead\n");
		loadOBJ("cube.obj",vVerts,vTexts,vNorms);
	}
	
	glGenVertexArrays(1,&vArray);
	glBindVertexArray(vArray);

	glGenBuffers(1,&vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER,vVerts.size()*sizeof(glm::vec3),&vVerts[0],GL_STATIC_DRAW);

	glGenBuffers(1,&normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER,normalbuffer);
	glBufferData(GL_ARRAY_BUFFER,vNorms.size()*sizeof(glm::vec3),&vNorms[0],GL_STATIC_DRAW);

	glGenBuffers(1,&uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER,uvbuffer);
	glBufferData(GL_ARRAY_BUFFER,vTexts.size()*sizeof(glm::vec2),&vTexts[0],GL_STATIC_DRAW);

	if (textureFile.length() > 0) {
		myText = loadBMP(textureFile.c_str());
		//myText2 = loadBMP("stars.bmp");
		//myText2ID = glGetUniformLocation(program,"myTexture2");
		//for (int i = 0; i < vTexts.size(); i++)
		//	vTexts[i].x/20.0f;
		//addPosOffset = addOffset=true;
		if (hasBump) {
			//setup stuffs for bump-mapping
			myBump = loadBMP(bumpMap.c_str());
			computeTangents(vVerts, vTexts, vNorms, vTans, vBitans);

			glGenBuffers(1,&tanbuffer);
			glBindBuffer(GL_ARRAY_BUFFER,tanbuffer);
			glBufferData(GL_ARRAY_BUFFER,vTans.size()*sizeof(glm::vec3),&vTans[0],GL_STATIC_DRAW);
			
			glGenBuffers(1,&bitanbuffer);
			glBindBuffer(GL_ARRAY_BUFFER,bitanbuffer);
			glBufferData(GL_ARRAY_BUFFER,vBitans.size()*sizeof(glm::vec3),&vBitans[0],GL_STATIC_DRAW);
			fShad = "fshadfinalbump.glsl"; vShad = "vshadfinalbump.glsl";
		} else  if (isBlend) {
			vShad = "vshadfinalbasic.glsl"; fShad = "fshadfinalbasic.glsl";
		} else {
			vShad = "vshadfinal.glsl"; fShad = "fshadfinal.glsl";
		}
	}

	if (vShad.size() == 0) {
		cout << "Could not load shaders. Skipping object\n";
		return;
	}
	program = LoadShaders(vShad.c_str(),fShad.c_str());
	
	printf("%s %s\n",fShad.c_str(),vShad.c_str());
	myNormID = glGetUniformLocation(program,"vNorm");
	if (textureFile.length() > 0) {
		myTextID = glGetUniformLocation(program,"myTexture");
		if (hasBump) {
			myBumpMapID = glGetUniformLocation(program,"myBump");
		}
	}
}

void oglobj::setStaticRot(vec3 inRot) 
{
	hasStatRot = true;
	thetaStatic = inRot;
}

void oglobj::setBumpMap(string inName) 
{
	bumpMap = inName;
	hasBump = true;
}

void oglobj::render() 
{
	glUseProgram(program);
	vec3 tempPos = currPos;

	if (isBlend) {glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(0); }

	//These functions can handle scrolling a texture on an object and oscillation between two textures
	//commented out as I'm moving back to basic functionality
	//if (addOffset)currTextOffset+=.0001f;
	//else currTextOffset-=.0001f;
	//if (currTextOffset > 1.00f) addOffset=false;
	//else if (currTextOffset < 0.0f) addOffset=true;

	//if (addPosOffset)posOffset+=.001f;
	//else posOffset-=.001f;
	//if (posOffset > 1.00f) addPosOffset=false;
	//else if (posOffset < 95.0f) addPosOffset=true;

	//glUniform1f(glGetUniformLocation(program,"posOffset"),posOffset);
	//glUniform1f(glGetUniformLocation(program,"offset"),currTextOffset);

	
	if (parent == -1) {
		myProj = getProjMat();
		myView = getViewMat();
		model = mat4(1.0f);
	}

	if (hasStatRot) {
		model = glm::rotate(model,thetaStatic.x,vec3(1.0f,0.0f,0.0f));
		model = glm::rotate(model,thetaStatic.y,vec3(0.0f,1.0f,0.0f));
		model = glm::rotate(model,thetaStatic.z,vec3(0.0f,0.0f,1.0f));
	}
	
	if (rot) {
		if (axis == 'x') {
			thetaActive.x+=.25;
			if (thetaActive.x > 360.0) thetaActive.x-=360.0;
		} else if (axis == 'y') {
			thetaActive.y+=.25;
			if (thetaActive.y > 360.0) thetaActive.y-=360.0;
		} else if (axis == 'z') {
			thetaActive.z+=.25;
			if (thetaActive.z > 360.0) thetaActive.z-=360.0;
		}
		model = glm::rotate(model,thetaActive.x,vec3(1.0f,0.0f,0.0f));
		model = glm::rotate(model,thetaActive.y,vec3(0.0f,1.0f,0.0f));
		model = glm::rotate(model,thetaActive.z,vec3(0.0f,0.0f,1.0f));
	}
	if (hasPath) {
		if (pathDir == 'x') {
			if (toSecond) currPos.x+=dist/500;
			else currPos.x-=dist/500;
			if (fabs(currPos.x - (pos.x + dist)) < 0.0001)toSecond = false;
			else if (fabs(currPos.x - pos.x) < 0.0,1) toSecond = true;
		} else if (pathDir == 'y') {
			if (toSecond) currPos.y+=dist/500;
			else currPos.y-=dist/500;
			if (fabs(currPos.y - (pos.y+dist)) < 0.001) toSecond = false;
			else if (fabs(currPos.y - pos.y ) < 0.001) toSecond = true;
		} else if (pathDir == 'z') {
			if (toSecond) currPos.z+=dist/500;
			else currPos.z-=dist/500;
			if (fabs(currPos.z - (pos.z + dist)) < 0.001)toSecond = false;
			else if (fabs(currPos.z - pos.z) < 0.001) toSecond = true;
		}
	}

	model = glm::translate(model,tempPos);
	model = glm::scale(model,scale);
	mv = myView*model;

	//uniform float attConst0, attLin0, attQuad0;
	stringstream tmpID; vec3 tmpProd;

	for (int i = 0; i < lights.size(); i++) {
		tmpID.str(""); tmpID << "lightPos" << i;
		glUniform4fv(glGetUniformLocation(program,tmpID.str().c_str()),1,glm::value_ptr(lights[i].pos));
		tmpID.str(""); tmpID << "lightCol" << i; tmpProd = lights[i].col;
		glUniform3fv(glGetUniformLocation(program,tmpID.str().c_str()),1,glm::value_ptr(tmpProd));
	}
	glUniform1i(glGetUniformLocation(program,"numLights"),lights.size());

	glUniformMatrix4fv(glGetUniformLocation(program,"MV"),1,GL_FALSE,&mv[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program,"M"),1,GL_FALSE,&model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program,"V"),1,GL_FALSE,&myView[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program,"P"),1,GL_FALSE,&myProj[0][0]);

	glUniform3fv(glGetUniformLocation(program,"matAmb"),1,glm::value_ptr(mat.ambient));
	glUniform3fv(glGetUniformLocation(program,"matSpec"),1,glm::value_ptr(mat.specular));
	glUniform1fv(glGetUniformLocation(program,"matShi"),1,&mat.shine);

	if (isBlend) 
		glUniform1f(glGetUniformLocation(program,"alpha"),alpha);

	//Send all that other stuff
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_TRUE,0,(void*)0);
	
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER,normalbuffer);
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,(void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER,uvbuffer);
	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,0,(void*)0);

	//Bind our texture stuff
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,myText);
	glUniform1i(myTextID,0);
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D,myText2);
	//glUniform1i(myText2ID,1);
	if (hasBump) {
		//send 3x3 mv mat for bump mapping
		glm::mat3 mv3x3Mat = glm::mat3(mv);
		glUniformMatrix3fv(glGetUniformLocation(program,"MV3x3"),1,GL_FALSE, &mv3x3Mat[0][0]);
		
		//send bump map
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D,myBump);
		glUniform1i(myBumpMapID,1);

		//send tangents and bitangents
		glEnableVertexAttribArray(3);
		glBindBuffer(GL_ARRAY_BUFFER,tanbuffer);
		glVertexAttribPointer(3,3,GL_FLOAT,GL_FALSE,0,(void*)0);

		glEnableVertexAttribArray(4);
		glBindBuffer(GL_ARRAY_BUFFER,bitanbuffer);
		glVertexAttribPointer(4,3,GL_FLOAT,GL_FALSE,0,(void*)0);
	}

	glDrawArrays(GL_TRIANGLES,0,vVerts.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	if (isBlend) {glDisable(GL_BLEND); glDepthMask(1); }
}

oglobj::~oglobj(void)
{
}

