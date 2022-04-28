#ifndef __mesh_h__
#define __mesh_h__

#include <vector>
#include "shader.h"
#include "texture.h"

typedef struct{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
	glm::vec3 color;
}Vertex;


class Mesh{
public:
	Mesh();
	Mesh( const Mesh& m );
	std::vector<Vertex>       vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture>      textures;

	Mesh( std::vector<Vertex> vertices,
			std::vector<unsigned int> indices,
			std::vector<Texture> textures );
	void draw(Shader *s, bool wireframe = false );
	void loadAllVertices();
	void setupMesh( size_t maxBufferSize, size_t maxIndices);
	void setupMesh( ); //normal mode

	unsigned int VAO, VBO, EBO;

};

#endif
