#include "camera.h"
#include "ray.h"

// a and b are the pixel positions 
Ray Camera::generateRay(float a, float b)
{
	Point origin = center;
	Vector target =   a * across + b * up + Vector(corner);
	target.normalize();
	return Ray(origin, target);
}
