#include "terrainface.h"

TerrainFace::TerrainFace( int _resolution, glm::vec3 _localUp ){
	m_resolution = _resolution;

	m_axisLocalUp = _localUp;
	m_axisLocalUp = glm::normalize( m_axisLocalUp );

	m_axisForward = glm::vec3( 
			m_axisLocalUp.z,
			m_axisLocalUp.x,
			m_axisLocalUp.y );
	m_axisForward = glm::normalize( m_axisForward );

	m_axisRight = glm::cross( m_axisLocalUp, m_axisForward );
	m_axisRight = glm::normalize( m_axisRight );


	setupMesh( TF_MAX_RESOLUTION * TF_MAX_RESOLUTION * sizeof(Vertex),
		2 * 3 * (TF_MAX_RESOLUTION - 1) * (TF_MAX_RESOLUTION - 1) );
}

void TerrainFace::constructMesh( float umin, float umax, float vmin, float vmax ){
	Vertex *verts = new Vertex[m_resolution * m_resolution];
	unsigned int* triangles = new unsigned int[ 2*3*(m_resolution - 1)*(m_resolution-1)];
	unsigned int  triIdx = 0;
	for( unsigned int z = 0; z < m_resolution; z++ ){
		for( unsigned int x = 0; x < m_resolution; x++ ){
			int i = x + z * m_resolution;

			/* Create Vertices and Texture Coordinates */
			glm::vec2 percent( (float)x / (m_resolution - 1), (float)z / (m_resolution - 1) );
			/* move up 1 unit, move from -1 -> +1 on the X and Z axis */
			/* convert 0->2 to -1->1 by subtracting 1 */
			glm::vec3 pointOnUnitCube = m_axisLocalUp + 
				(2 * percent[0] - 1.0f) * m_axisRight + 
				(2 * percent[1] - 1.0f) * m_axisForward; 
			glm::vec3 pointOnUnitSphere = glm::normalize( pointOnUnitCube );
			glm::vec3 p = pointOnUnitSphere;

 			float a = 6378137.0;
			//a += 4000000.0;
			float b = 6356752.314245;
			//a = 1; b = 1;

#define PI acos(-1)
			float phi   = asin(p[1]);
			float theta = atan(-p[2]/p[0]);
			if( p[0] == 0 && p[2] == 0 ) theta = 0;

			if( p[0] < 0 ) theta = theta - PI;
			//fprintf(stdout, "%d: %10.5f, %10.5f\n", 
			//		i,phi*180/PI,theta*180/PI);
			float N = ( a * a ) / 
				sqrt( a*a*cos2(phi)+b*b*sin2(phi) );

			Vertex current;
			current.position[0] = N * cosf( phi ) * cosf( theta );
			current.position[1] = N * cosf( phi ) * sinf( theta );
			current.position[2] = ((b*b)/(a*a)) * N * sinf( phi );

			glm::mat3 toNDC(
					0, 1, 0,
					0, 0, 1,
					1, 0, 0
				       );

			verts[i].position = current.position * toNDC;
			//verts[i].position = p;
			//verts[i].normal    = m_axisLocalUp; //TODO: ONLY WORKS FOR CUBE
			/* Figure out texture coordinates.... */
			glm::vec2 u(umin, umax); //x
			glm::vec2 v(vmin, vmax); //y
			verts[i].texCoords = glm::vec2( u[0] + (    percent[0])*(u[1]-u[0]) , 
						        v[0] + (1.0-percent[1])*(v[1]-v[0]) );
			//verts[i].texCoords = glm::vec2( vmin + percent[1]*vmax, umin + percent[0]*umax );
			verts[i].color     = glm::vec3( 1.0 );

			/* Create Indices */
			if( x != m_resolution - 1 && z != m_resolution - 1 ){
				triangles[triIdx++] = i;
				triangles[triIdx++] = i+m_resolution;
				triangles[triIdx++] = i+m_resolution+1;

				triangles[triIdx++] = i;
				triangles[triIdx++] = i+m_resolution+1;
				triangles[triIdx++] = i+1;
			}
		}
	}
	vertices.clear();
	indices.clear();
	for( unsigned int i = 0; i < 2 * (m_resolution - 1) * (m_resolution - 1 ); i++ ){
		unsigned int current[3];
		current[0] = triangles[i*3+0];
		current[1] = triangles[i*3+1];
		current[2] = triangles[i*3+2];

		/* 0,
		 * 4, 5
		 */
		indices.push_back( current[0] );
		indices.push_back( current[1] );
		indices.push_back( current[2] );
		glm::vec3 a = 
			verts[current[1]].position -
			verts[current[0]].position ;
		glm::vec3 b = 
			verts[current[2]].position -
			verts[current[0]].position ;

		glm::vec3 normal = 
			glm::normalize(glm::cross( a, b ) );
		verts[triangles[i*3+0]].normal = normal;
		verts[triangles[i*3+1]].normal = normal;
		verts[triangles[i*3+2]].normal = normal;
	}
	for( unsigned int i = 0; i < m_resolution * m_resolution; i++){
		vertices.push_back( verts[i] );
	}
	delete [] triangles;
	delete [] verts;

	loadAllVertices();
}

void TerrainFace::loadTexture(const char* path, const char* type){
	m_texID = ::loadTexture(path);
	textures.push_back(Texture(m_texID,type));
}
