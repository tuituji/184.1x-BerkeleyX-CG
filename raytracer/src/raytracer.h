#ifndef _RAYTRACER_H
#define _RAYTRACER_H

#include <stack>
#include <string>
#include "scene.h"

using namespace std;

class RayTracer {
public:
	RayTracer(char *filename):input(filename) { 
		scene = new Scene; 
		maxdepth = 1;
		// load identity
//		transStack.Push(Matrix4x4(1.0));
	}
	void trace();

	Scene *scene;	
	Film film;
    Camera* camera;

	MatrixStack transStack;
	int width;
	int height;
	int maxdepth;
private:
	string input;
};

#endif
