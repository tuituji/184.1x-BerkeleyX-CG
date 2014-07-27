#ifndef _SCENE_H
#define _SCENE_H

#include <vector>
#include <cstdio>
#include <cstring>
#include "camera.h"
#include "light.h"
#include "shape.h"
#include "primitive.h"
#include "bvh.h"


using namespace std;

inline unsigned char max(unsigned char a, unsigned char b)
{
	return (a>b? a:b);
}

inline unsigned char min(unsigned char a, unsigned char b)
{
	return (a<b? a:b);
}

class Film {
public:
	Film() : width(400), height(300) { } ;
	Film(int w, int h): width(w), height(h) { 
		bitmap = new unsigned char[width * height * 3];
	};

	int width, height;
	unsigned char *bitmap;
	inline void setPixel(int i, int j, Color col) {
		unsigned char r = min((unsigned char)(col.r * 255), 255);
		unsigned char g = min((unsigned char)(col.g * 255), 255);
		unsigned char b = min((unsigned char)(col.b * 255), 255);
		int idx = (i* width + j) * 3;
		bitmap[idx++] = r;
		bitmap[idx++] = g;
		bitmap[idx++] = b;
	}
	void outFilm(const char *file_name) {
		FILE *fp = fopen(file_name, "w");
//		char head[32];
//		sprintf(head, "P6\n%d %d\n255\n", width, height);
//		fwrite(head, strlen(head), 1, fp);
		fprintf(fp, "P6\n%d %d\n255\n", width, height);
		fwrite(bitmap, width * 3, height, fp);
		fclose(fp);
	}
};

typedef float Vec3f[3];

class Scene {
public:
//	Scene() { };
//	Scene(const Film & f) : film(f) { };
	~Scene()  {
		if(verts) delete[] verts;
		// and free primitive
		// and free lights
	}
	bool Intersect(const Ray &ray,  HitRecord& record);

	void addShape(Shape* s) {  shapes.push_back(s);  }
//	vector<Primitive*> primitives;	
	vector<Shape*> shapes;
	Vec3f* verts;	
	int num_verts;
	vector<Light*> lights;
//	int width, height;	
	Color Radiance(Ray &r, int depth);

	void buildBVH();
	BVH *mBVH;
};

#endif
