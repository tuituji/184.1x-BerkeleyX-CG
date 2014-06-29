
#include "raytracer.h"
#include "ray.h"

void RayTracer::trace()
{
	int i, j;
	int depth = 10;
//	Ray ray = Ray(Point(0, 0, 4), Vector(0.2, -0.2, -1));
//	Ray ray = Ray(Point(0, 0, 4), Vector(0, 0, -1));
//	Color col = scene->Radiance(ray, depth);
//	printf("col.r %f, col.g %f, col.b: %f\n", col.r, col.g, col.b);

	for(i = 0; i < height; ++i){
		for(j = 0; j < width; ++j){
			// samples here
			Ray ray = camera->generateRay(j/(double)width, i/(double)height);
			Color col = scene->Radiance(ray, depth);
			if(col.r >0 || col.g > 0 ||  col.b >0) {
				film.setPixel( height - i - 1, j ,col);
			}
		}
	}
	film.outFilm("out.ppm");
}



