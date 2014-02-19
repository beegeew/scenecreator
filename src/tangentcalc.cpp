//Developed with help from opengl-tutorial.org
//

#include "tangentcalc.h"

void computeTangents(vector<glm::vec3> &vVerts, vector<glm::vec2> &vTexts,
	vector<glm::vec3> vNorms, vector<glm::vec3> &vTans, vector<glm::vec3> & vBitans)
{
	for (unsigned int i=0; i<vVerts.size(); i+=3 ){

		glm::vec3 &v0 = vVerts[i+0]; glm::vec3 &v1 = vVerts[i+1]; glm::vec3 &v2 = vVerts[i+2];

		glm::vec2 &uv0 = vTexts[i+0]; glm::vec2 &uv1 = vTexts[i+1]; glm::vec2 &uv2 = vTexts[i+2];

		glm::vec3 deltaPos1 = v1-v0;
		glm::vec3 deltaPos2 = v2-v0;

		glm::vec2 deltaUV1 = uv1-uv0;
		glm::vec2 deltaUV2 = uv2-uv0;

		float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
		glm::vec3 tangent = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y)*r;
		glm::vec3 bitangent = (deltaPos2 * deltaUV1.x   - deltaPos1 * deltaUV2.x)*r;

		vTans.push_back(tangent); vTans.push_back(tangent); vTans.push_back(tangent);

		vBitans.push_back(bitangent);
		vBitans.push_back(bitangent);
		vBitans.push_back(bitangent);
	}

	for (unsigned int i=0; i<vVerts.size(); i+=1 )
    {
        glm::vec3 &n = vNorms[i];
        glm::vec3 &t = vTans[i];
        glm::vec3 &b = vBitans[i];
        
		t = glm::normalize(t - n * glm::dot(n, t));
		if (glm::dot(glm::cross(n, t), b) < 0.0f){
			t = t * -1.0f;
		}
    }
}
