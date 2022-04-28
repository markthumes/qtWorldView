#include "mesh.h"

Mesh::Mesh(){
	VAO = 0;
	VBO = 0;
	EBO = 0;
	vertices.clear();
	indices.clear();
	textures.clear();
};

Mesh::Mesh(	std::vector<Vertex>       _vertices,
		std::vector<unsigned int> _indices,
		std::vector<Texture>      _textures ){
	vertices = _vertices;
	indices  = _indices;
	textures = _textures;
	VAO = 0;
	VBO = 0;
	EBO = 0;

	setupMesh();
}

Mesh::Mesh( const Mesh& m ){
	vertices = m.vertices;
	indices  = m.indices;
	textures = m.textures;
	VAO = m.VAO;
	VBO = m.VBO;
	EBO = m.EBO;
}

void Mesh::loadAllVertices(){
	size_t offset = 0;
	size_t datasz = 0;
	float* storage = NULL;

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Positions
	datasz = vertices.size() * 3 * sizeof(float);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)offset);
	storage = new float[datasz];
	for(unsigned int i = 0; i < vertices.size(); i++){
		for(unsigned int j = 0; j < 3; j++){
			storage[j+i*3] = vertices[i].position[j];
		}
	}
	glBufferSubData(GL_ARRAY_BUFFER, offset, vertices.size() * 3 * sizeof(float), storage );
	delete [] storage;
	offset += datasz;
	//Normals
	datasz = vertices.size() * 3 * sizeof(float);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)offset);
	storage = new float[datasz];
	for(unsigned int i = 0; i < vertices.size(); i++){
		for(unsigned int j = 0; j < 3; j++){
			storage[j+i*3] = vertices[i].normal[j];
		}
	}
	glBufferSubData(GL_ARRAY_BUFFER, offset, vertices.size() * 3 * sizeof(float), storage );
	delete [] storage;
	offset += datasz;
	//Textures
	datasz = vertices.size() * 2 * sizeof(float);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)offset);
	storage = new float[datasz];
	for(unsigned int i = 0; i < vertices.size(); i++){
		for(unsigned int j = 0; j < 2; j++){
			storage[j+i*2] = vertices[i].texCoords[j];
		}
	}
	glBufferSubData(GL_ARRAY_BUFFER, offset, vertices.size() * 3 * sizeof(float), storage );
	delete [] storage;
	offset += datasz;
	//Colors
	datasz = vertices.size() * 3 * sizeof(float);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)offset);
	storage = new float[datasz];
	for(unsigned int i = 0; i < vertices.size(); i++){
		for(unsigned int j = 0; j < 3; j++){
			storage[j+i*3] = vertices[i].color[j];
		}
	}
	glBufferSubData(GL_ARRAY_BUFFER, offset, vertices.size() * 3 * sizeof(float), storage );
	delete [] storage;
	offset += datasz;

	//Indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(unsigned int),
			&indices[0] );

	glBindVertexArray(0);
	storage = NULL;
}

void Mesh::setupMesh( ){
	glGenVertexArrays( 1, &VAO );
	glGenBuffers( 1, &VBO );
	glGenBuffers( 1, &EBO );

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
			&indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glBindVertexArray(0);

}
void Mesh::setupMesh( size_t maxBufferSize, size_t maxIndices ){
	glGenVertexArrays( 1, &VAO );
	glGenBuffers( 1, &VBO );
	glGenBuffers( 1, &EBO );

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, maxBufferSize, NULL,
			GL_STATIC_DRAW );

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, maxIndices * sizeof(unsigned int),
			NULL, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void Mesh::draw(Shader *shader, bool wireframe ){
	shader->use();
	/* Experiment with moving the texture binding elsewhere */
	unsigned int diffuseNr  = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr   = 1;
	unsigned int heightNr   = 1;
	for( unsigned int i = 0; i < textures.size(); i++ ){
		int number;
		glActiveTexture(GL_TEXTURE0 + i);
		if( strcmp("texture_diffuse", textures[i].type) == 0 ){
			number = diffuseNr++;
		}
		else if( strcmp("texture_specular", textures[i].type) == 0 ){
			number = specularNr++;
		}
		else if( strcmp("texture_normal", textures[i].type) == 0 ){
			number = normalNr++;
		}
		else if( strcmp("texture_height", textures[i].type) == 0 ){
			number = heightNr++;
		}
		char temp[100];
		sprintf(temp, "%s%d", textures[i].type, number);
		shader->setInt( temp, i );
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	glBindVertexArray(VAO);
	glPolygonMode( GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL );
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0 );
	//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0 );
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}
