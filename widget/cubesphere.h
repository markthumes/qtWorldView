#ifndef __cubesphere_h__
#define __cubesphere_h__

#include "mesh.h"
#include "terrainface.h"
#include "shader.h"
#define DEG2RAD acos(-1) / 180.0f;
#define CUBEFACES 6

class CubeSphere{
public:
	CubeSphere(unsigned int _resolution = 4, 
			glm::vec3 _pos = glm::vec3(0.0));
	CubeSphere( const CubeSphere &cs );
	~CubeSphere();
	void generateMesh();
	void draw(Shader *shader, bool wf = false);
	unsigned int& resolution();
	void init();
	unsigned int texID;
	void loadCubeMap( const char* path );
	Texture tex;
	bool& showNormals();
	bool& showEdges();
	glm::vec3 &position();
protected:
	void fin();
private:
	TerrainFace* m_terrainFace[CUBEFACES];
	unsigned int m_resolution;
	bool m_normalsVisible;
	bool m_edgesVisible;
	glm::vec3 m_position;
};

#endif
