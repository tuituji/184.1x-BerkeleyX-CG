#ifndef _MESH_H
#define _MESH_H

#include <vector>
#include <cstdio>
#include <cstdlib>
#include "shape.h"
#include "ray.h"
#include "scene.h"

class Mesh : public Shape {
public:
	Mesh(Scene *s): scene_ptr(s) { 
		num_verts = scene_ptr->num_verts;
		verts = new Vec3f[num_verts];
	};
	~Mesh() {
		delete[] verts;
	}	
//	bool intersect(const Ray& r, HitRecord& t);
//	vector<Triangle* > tris;
	Scene *scene_ptr;
	Vec3f* verts;
	int num_verts;
	Material material;	
};

class Triangle: public Shape {
public:
	Triangle(int id0, int id1, int id2, Mesh *m_ptr) {
		idx[0] = id0; idx[1]= id1; idx[2] = id2;
		mesh_ptr = m_ptr;
	}
	bool intersect(const Ray &ray, HitRecord &r);
	int idx[3];
	Mesh *mesh_ptr;
	Material material;	
	
	void updateBoundingBox();

	Material getMaterial() const {
		return mesh_ptr->material;
	}
};



#endif
