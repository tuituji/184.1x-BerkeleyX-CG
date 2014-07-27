#include "camera.h"
#include "ray.h"

// a and b are the pixel positions 
Ray Camera::generateRay(float a, float b)
{
	Point origin = center;
	Vector dir =   a * across + b * up + Vector(corner);
	dir.normalize(); // ok must normalize the ray direction
	return Ray(origin, dir);
}
