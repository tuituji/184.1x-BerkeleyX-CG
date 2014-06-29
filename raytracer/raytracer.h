#ifndef _RAYTRACER_H
#define _RAYTRACER_H

#include <stack>
#include "scene.h"

class RayTracer {
public:
	RayTracer() { 
		scene = new Scene; 
		// load identity
		transStack.push(Matrix4x4(1.0));
	}
	void trace();

	Scene *scene;	
	Film film;
    Camera* camera;

	stack <Matrix4x4> transStack;
	int width;
	int height;
};

#endif
