#include "conversions.h"

/* Geodetic to ECEF */
glm::vec3 lla2ecef( glm::vec3 lla, float _a, float _b ){
	glm::vec3 ecef;
	float a = _a;
	float b = _b;
	float n_theta;

	float a2 = a*a;
	float b2 = b*b;
	float e2 = 1 - (b2/a2);

	//n_theta = a2 / sqrt( a2*cos2(lla[0]) + b2*sin2(lla[0]) );
	n_theta = a / sqrt( 1 - e2*sin2(lla[0]) );
	ecef[0] = (n_theta + lla[2])*cos(lla[0])*cos(lla[1]);
	ecef[1] = (n_theta + lla[2])*cos(lla[0])*sin(lla[1]);
	ecef[2] = ((b2/a2)*n_theta+lla[2])*sin(lla[0]);

	return ecef;
}

/* ECEF to Geodetic */
glm::vec3 ecef2lla( glm::vec3 ecef ){
	glm::vec3 lla;
}
