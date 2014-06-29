#ifndef _SHAPE_H
#define _SHAPE_H


#include <vector>
#include <cstdio>
#include "material.h"
#include "geometry.h"
#include "shape.h"
#include "ray.h"

using namespace std;

class HitRecord;

class Shape {
public:
	virtual bool intersect(const Ray&r, HitRecord& record){
		fprintf(stderr, "intersect not implemented yet\n");
		return false;
	}
	void setMaterial(const Material &m) {
		material = m;	
	}
	void setMatrix(const Matrix4x4 &m) {
		transform = m;
		transform_inv = m.Inverse();
	}
	Material material;
	Matrix4x4 transform;
	Matrix4x4 transform_inv;
};


class HitRecord {
public:
	HitRecord() : pos(), normal(), t(0.0), obj(NULL) { };

//	Color color;
	Point pos;// do we need pos ?? 
	Vector normal;
	float t;
	Shape *obj;
};

class Sphere : public Shape {
public:
	Sphere(const Point& p, float r) : center(p), radius(r) { };
	bool intersect(const Ray& ray, HitRecord& r);
	Point center;
	float radius;
};

class Plane : public Shape {
public:
	Plane(Vector n, float d): normal(n), distance(d) {
		normal.normalize();
		position = normal * distance;
	};
	bool intersect(const Ray& ray, HitRecord& r);

	Vector normal;
	float distance;
private:
	Point position;
};

#endif
