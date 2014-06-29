#ifndef _MESH_H
#define _MESH_H

#include <vector>
#include <cstdio>
#include <cstdlib>
#include "shape.h"
#include "ray.h"
#include "scene.h"

class Mesh;

class Triangle {
public:
	Triangle(int id0, int id1, int id2) {
		idx[0] = id0; idx[1]= id1; idx[2] = id2;
	}
	bool intersect(const Ray &ray, HitRecord &r);
	int idx[3];
	Mesh *mesh_ptr;
	
};

class Mesh : public Shape {
public:
	Mesh(Scene *s): scene_ptr(s) { };
	~Mesh() {
		vector<Triangle*>::iterator iter;
		for(iter = tris.begin(); iter != tris.end(); ++iter) {
//			delete iter;
		}
	}	
	void addTriangle(Triangle* tri){
		tri->mesh_ptr = this;
		tris.push_back(tri);
	}
	bool intersect(const Ray& r, HitRecord& t);
	vector<Triangle* > tris;
	Scene *scene_ptr;
};


#endif
