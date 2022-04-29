#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "mesh.h"
#include "conversions.h"
#include <math.h>

class Sphere : public Mesh {
public:
	Sphere( uint stacks, uint sectors, float major, float minor );
	Sphere( uint stacks, uint sectors, float radius );
	void generate();
private:
	unsigned int m_stacks;
	unsigned int m_sectors;
	float        m_major;
	float        m_minor;
};

#endif //__SPHERE_H__
