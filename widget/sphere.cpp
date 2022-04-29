#include "sphere.h"

Sphere::Sphere( uint stacks, uint sectors, float major, float minor ):Mesh(){
	m_stacks = stacks;
	m_sectors = sectors;
	m_major = major;
	m_minor = minor;
	generate();
}
Sphere::Sphere( uint stacks, uint sectors, float radius ):Mesh(){
	m_stacks = stacks;
	m_sectors = sectors;
	m_major = radius;
	m_minor = radius;
	generate();
}
void Sphere::generate(){
	vertices.clear();
	indices.clear();
	float a = m_major;
	float b = m_minor;

	/* Vertex and UV map construction */
	for( unsigned int i = 0; i <= m_stacks; i++ ){
		unsigned int csectors = m_sectors;
		if( i == 0 || i == m_stacks ) csectors--;

		float phi   = PI / 2 - i * PI / m_stacks;

		for( unsigned int j = 0; j <= csectors; j++ ){

			float N = ( a * a ) / 
				sqrt( a*a*cos2(phi)+b*b*sin2(phi) );
			float theta = 0 + 2 * PI * j / m_sectors;

			struct VertexData current;
			current.position[0] = N * cosf( phi ) * cosf( theta );
			current.position[1] = N * cosf( phi ) * sinf( theta );
			current.position[2] = ((b*b)/(a*a)) * N * sinf( phi );

			float u = (float)j / csectors ;
			float v = (float)i / m_stacks ;

			current.texCoord = QVector2D( u, v );
			current.color = QVector3D( u, 1.0, 1.0 );
			current.normal = current.position.normalized();
			vertices.push_back(current);
		}
	}

	unsigned int k1 = 0;
	unsigned int k2 = 0;
	for( unsigned int i = 0; i < m_stacks; i++ ){
		unsigned int csectors = m_sectors + 1;
		if( i == 0 ) csectors -= 1;
		for( unsigned int j = 0; j < csectors; j++){

			/* TOP ROW */
			if( i == 0 ){
				k1 = i * csectors + j;
				k2 = k1 + csectors + 0;
				indices.push_back( k1   );
				indices.push_back( k2   );
				indices.push_back( k2+1 );
			}
			/* BOTTOM ROW */
			else if( i == m_stacks - 1 ){
				k1 = i * csectors + j - 1;
				k2 = k1 + csectors;
				indices.push_back( k1   );
				indices.push_back( k2   );
				indices.push_back( k1+1);
				if( j == csectors - 2) break;
			}
			else{
				k1 = i * csectors + j - 1;
				k2 = k1 + csectors;
				indices.push_back( k1   );
				indices.push_back( k2   );
				indices.push_back( k2+1 );

				indices.push_back( k1   );
				indices.push_back( k2+1 );
				indices.push_back( k1+1 );
			}

		}
	}
	init();
}
