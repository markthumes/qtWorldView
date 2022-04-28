#include "cubesphere.h"

CubeSphere::CubeSphere(unsigned int _resolution, glm::vec3 _pos){
	resolution() = _resolution;
	position()   = _pos;
}

CubeSphere::~CubeSphere(){
	fin();
}

unsigned int& CubeSphere::resolution(){
	return m_resolution;
}

glm::vec3& CubeSphere::position(){
	return m_position;
}

void CubeSphere::draw(Shader *shader, bool wf){
	for( unsigned int i = 0; i < CUBEFACES; i++){
		m_terrainFace[i]->draw(shader,wf);
	}
}

void CubeSphere::init(){
	glm::vec3 direction[] = {
		glm::vec3( 0, 1, 0 ), //up
		glm::vec3( 0,-1, 0 ), //down

		glm::vec3(-1, 0, 0 ), //left
		glm::vec3( 1, 0, 0 ), //right

		glm::vec3( 0, 0, 1 ), //forward
		glm::vec3( 0, 0,-1 ), //back
	};
	for( int i = 0; i < CUBEFACES; i++ ){
		m_terrainFace[i] = new TerrainFace(
				m_resolution,
				direction[i]
				);
	}
}

void CubeSphere::generateMesh(){
	for( int i = 0; i < CUBEFACES; i++ ){
		m_terrainFace[i]->m_resolution = m_resolution;
	}
	float  widthSegments = 1.0/4.0;
	float heightSegments = 1.0/3.0;
	m_terrainFace[0]->constructMesh();//widthSegments*1, widthSegments*2, heightSegments*2, heightSegments*3); //up
	m_terrainFace[0]->loadTexture("images/top.png", "texture_diffuse");
	m_terrainFace[1]->constructMesh();//widthSegments*1, widthSegments*2, heightSegments*0, heightSegments*1); //down
	m_terrainFace[1]->loadTexture("images/bottom.png", "texture_diffuse");
	m_terrainFace[2]->constructMesh();//widthSegments*0, widthSegments*1, heightSegments*1, heightSegments*2); //left
	m_terrainFace[2]->loadTexture("images/left.png", "texture_diffuse");
	m_terrainFace[3]->constructMesh();//widthSegments*2, widthSegments*3, heightSegments*1, heightSegments*2); //right
	m_terrainFace[3]->loadTexture("images/right.png", "texture_diffuse");
	m_terrainFace[4]->constructMesh();//widthSegments*1, widthSegments*2, heightSegments*1, heightSegments*2); //forward
	m_terrainFace[4]->loadTexture("images/front.png", "texture_diffuse");
	m_terrainFace[5]->constructMesh();//widthSegments*3, widthSegments*4, heightSegments*1, heightSegments*2); //back
	m_terrainFace[5]->loadTexture("images/back.png", "texture_diffuse");
}

bool& CubeSphere::showNormals(){
	return m_normalsVisible;
}
bool& CubeSphere::showEdges(){
	return m_edgesVisible;
}

/* NO */
void CubeSphere::loadCubeMap( const char* path ){
	tex.id = loadTexture(path);
	tex.type = "texture_diffuse";
	for( int i = 0; i < CUBEFACES; i++ ){
		m_terrainFace[i]->textures.push_back(Texture(tex.id,tex.type));
	}
}

void CubeSphere::fin(){
	for( int i = 0; i < CUBEFACES; i++ ){
		delete m_terrainFace[i];
	}
}
