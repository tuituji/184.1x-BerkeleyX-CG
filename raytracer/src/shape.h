#ifndef _SHAPE_H
#define _SHAPE_H


#include <vector>
#include <cstdio>
#include "material.h"
#include "geometry.h"
#include "ray.h"
#include "bbox.h"

using namespace std;

class HitRecord;

class Shape {
public:
	virtual bool intersect(const Ray&r, HitRecord& record){
		fprintf(stderr, "intersect not implemented yet\n");
		return false;
	}
	virtual Material getMaterial() const {
		fprintf	(stderr, "getMaterial not implement\n");
		return Material();
	}
	virtual BBox  boundingBox() { return bbox; }
//	void setMatrix(const Matrix4x4 &m) {
//		transform = m;
//		transform_inv = m.Inverse();
//	}
	virtual void updateBoundingBox() {
		fprintf(stderr, "updateBoundingBox not implemented\n");
	}
//	Material material;
//	Matrix4x4 transform;
//	Matrix4x4 transform_inv;
	BBox bbox;
};

#define INF 1e20

class HitRecord {
public:
	HitRecord() : pos(), normal(), t(INF), obj(NULL) { };

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
	void updateBoundingBox();
	
	Material getMaterial() const {
		return material;
	}
	Material material;
};

class Plane : public Shape {
public:
	Plane(Vector n, float d): normal(n), distance(d) {
		normal.normalize();
		position = normal * distance;
	};
	bool intersect(const Ray& ray, HitRecord& r);
	Material getMaterial() const {
		return material;
	}
	
	Vector normal;
	float distance;
	Material material;
private:
	Point position;
};

#endif
