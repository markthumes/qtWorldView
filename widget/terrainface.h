#ifndef __terrainface_h__
#define __terrainface_h__

#include "mesh.h"
#include "shader.h"
#include "conversions.h"

#define TF_MAX_RESOLUTION 20
class TerrainFace : public Mesh {
public:
	TerrainFace( int _resolution, glm::vec3 _up );
void constructMesh( float umin = 0, float umax = 1, float vmin = 0, float vmax = 1 );
	unsigned int 	m_resolution;

	void loadTexture(const char* path, const char* type);

protected:
private:
	glm::vec3 	m_axisLocalUp;
	glm::vec3	m_axisForward;
	glm::vec3	m_axisRight;
	unsigned int	m_texID;
};

#endif
