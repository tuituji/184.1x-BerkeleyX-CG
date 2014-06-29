#include "shape.h"

bool Plane::intersect(const Ray& ray, HitRecord& record)
{
	float a = ray.dir * normal;
	if(a >= 0)
		return false;
	
	float b = normal * (ray.pos - position);
	record.obj = this;
	record.t = - b / a;
	record.pos = ray.pos + record.t * ray.dir;
	record.normal = normal;
	return true;
}
