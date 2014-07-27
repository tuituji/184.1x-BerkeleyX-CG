
#include "raytracer.h"
#include "ray.h"
#include <cstdio>

void RayTracer::trace()
{
	int i, j;

	string name = input.substr(input.find_last_of("/") + 1);
	string output = name + ".ppm"	;
	
	scene->buildBVH();      // update BVH   
	

	for(i = 0; i < height; ++i){
	fprintf(stderr,"\rRendering  %5.2f%%", 100.*i/(height));
		for(j = 0; j < width; ++j){
			// samples here
			Ray ray = camera->generateRay(j/(double)width, i/(double)height);
			Color col = scene->Radiance(ray, maxdepth);
			film.setPixel( height - i - 1, j ,col);
		}
	}
	film.outFilm(output.c_str());
}



