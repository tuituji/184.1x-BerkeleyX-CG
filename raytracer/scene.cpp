#include <vector>
#include <cassert>
#include "scene.h"
#include "shape.h"

bool Scene::Intersect(const Ray &ray,  HitRecord& record)
{
	float t; // t record the current smallest
	float inf = 1e20;
	t = record.t = inf;
	vector<Shape*>::iterator itr;
	for(itr = shapes.begin(); itr != shapes.end(); ++itr) {
		if((*itr)->intersect(ray, record) && record.t < t) {
			t = record.t;
			record.obj = *itr;
		}
	}
	if(t < inf){
		record.t = t;
		record.pos = Point(ray.pos + t * ray.dir);
		return true;
	}
	return false;
}


Color Scene::Radiance(Ray &ray, int depth)
{
	HitRecord record;
	if(depth -- == 0){
		return Color(0.0, 0.0, 0.0);
	} // depth to max

	if(!Intersect(ray, record)) {
		return Color(0.0, 0.0, 0.0); // if not hit  return black;
	}

	// if hit
	Color col, col1;
	Color diffuse;
	Color specular;
	Vector L, R, H;
	float bf = 0.5;

	const Shape& obj = *(record.obj);	
	const Material& mat = obj.material;
	col = mat.ambient;
	R = reflect(ray.dir, record.normal);// get the reflected ray
	// to get the radiance value
	vector<Light*>::iterator itr;
	HitRecord record1;
	for(itr = lights.begin(); itr != lights.end(); ++itr) {
		// should first check the light type;
		L = -((*itr)->getDir(record.pos));  //(*itr).pos - record.pos;

#if 1
		Ray ray1 = Ray(record.pos, L);
		if(Intersect(ray1, record1)) {
//			if(record1.obj == record.obj){
//				if(record1.pos != record.pos){
//					printf("may come to error\n");
//				}
//			}	
			continue;// if light is shadowed the pass
		}
#endif
		H = (L -ray.dir)/2;
		// else not shadowed
		float nDotL = record.normal * L;
		float nDotH = record.normal * H;
		diffuse += (*itr)->col * ( nDotL >0 ? nDotL : 0);
		specular += (*itr)->col * pow((nDotH ? nDotH : 0), mat.shiness);	
	}

	col += mat.diffuse * diffuse + mat.specular * specular;
#if 1 
	// recursive call
	Ray ref = Ray(record.pos, R);
	col1 = Radiance(ref, depth);
	col = col  + col1 * bf;
#endif
	col.clamp();

	return col;
}
