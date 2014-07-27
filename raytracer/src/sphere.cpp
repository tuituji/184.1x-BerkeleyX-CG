#include "shape.h"


void Sphere::updateBoundingBox()
{
	const float epsilon = 0.00001f;
	Vector min, max;

	min.x = center.x -radius - epsilon;
	min.y = center.y -radius - epsilon;
	min.z = center.z -radius - epsilon;

	max.x = center.x + radius + epsilon;	
	max.y = center.y + radius + epsilon;
	max.z = center.z + radius + epsilon;

	bbox = BBox(min, max);
}

bool Sphere::intersect(const Ray& ray, HitRecord& record)
{
	Vector op = center - ray.pos;
	float eps = 1e-3;
	float b = op * ray.dir;
	float det = b * b - op * op + radius * radius;
	float t;	

	if(det < 0) 
		return false;
	else 
		det = sqrt(det);

	t = b - det;
	if(t < eps){ 
		t = b + det;
		if(t < eps) 
			return false;
	}

	record.t = t;
	record.obj = this;
	record.pos = ray.pos + record.t * ray.dir;
	record.normal = record.pos - center;
	record.normal.normalize();

	return true;
}

