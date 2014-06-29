#include "shape.h"

bool Sphere::intersect(const Ray& ray, HitRecord& record)
{
	Vector op = center - ray.pos;
	float eps = 1e-4;
	float b = op * ray.dir;
	float det = b * b - op * op + radius * radius;

	if(det < 0) 
		return false;
	else 
		det = sqrt(det);

	record.t = b - det;
	if(record.t < eps){ 
		record.t = b + det;
		if(record.t < eps) 
			return false;
	}
	record.obj = this;
	record.normal = Vector(ray.pos + record.t * ray.dir - center);
	record.normal.normalize();
	return true;
}

