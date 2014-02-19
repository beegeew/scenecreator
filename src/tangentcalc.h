#ifndef _tangent_h
#define _tangent_h

#include <vector>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

void computeTangents(vector<glm::vec3> &vVerts, vector<glm::vec2> &vTexts,
	vector<glm::vec3> vNorms, vector<glm::vec3> &vTans, vector<glm::vec3> & vBitans);

#endif
