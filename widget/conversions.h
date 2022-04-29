#ifndef __CONVERSIONS_H__
#define __CONVERSIONS_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define cos2(x) cosf(x)*cosf(x)
#define sin2(x) sinf(x)*sinf(x)
#define PI 2*acos(0.0)

/* Geodetic to ECEF */
glm::vec3 lla2ecef( glm::vec3 lla, float _a = 6378137.0, float _b = 6356752.314245 );

/* ECEF to Geodetic */
glm::vec3 ecef2lla( glm::vec3 ecef );

#endif //__CONVERSIONS_H__
