#include <vector>
#include <cassert>
#include "scene.h"
#include "shape.h"

bool Scene::Intersect(const Ray &ray,  HitRecord& record)
{

	return mBVH->intersect(ray, record);
#if 0
	float inf = 1e20;
	record.t = inf;
	vector<Shape*>::iterator itr;
	for(itr = shapes.begin(); itr != shapes.end(); ++itr) {
//		Point o = (*itr)->transform_inv * ray.pos;
//		Vector dir = (*itr)->transform_inv * ray.dir;
		const Point& o = ray.pos ;
		const Vector& dir = ray.dir;  // notice we still normalize it here
						  // whether not to changed it but to changed the 
						  // shape intersect function ??
		Ray tray(o, dir); // t will not be the same 
		HitRecord record0;
		// here shape->intersect will return everything
		if((*itr)->intersect(tray, record0) && record0.t < record.t) {
			record = record0;
		}
	}
	if(record.t < inf){
		// record.pos = Point(ray.pos + record.t * ray.dir);// the actual pos 
		// well since we have normalized the transformed vector
		// thus t is not the same
//		record.pos = record.obj->transform * record.pos;// the actual pos 
//		record.normal = (record.obj->transform_inv).Transpose()* record.normal;
		record.normal.normalize();// remember to normalize the normal
		return true;
	}
	return false;
#endif
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
	const Shape* obj = record.obj;	
	if(obj == NULL)	{
		printf("error here\n");
		printf("  t:%f\n", record.t);
		printf("  x:%f y:%f z:%f\n", record.pos.x, record.pos.y, record.pos.z);
		return Color(0.3, 0.3, 1.0);
		assert(obj != NULL);
	}
	const Material mat = obj->getMaterial();
	col = mat.ambient;
	col += mat.emission;
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
//  The following will not happen since we have add a bias to intersect t
//			if(record1.obj == record.obj){ 
//				if(record1.pos != record.pos){
//					printf("may come to error\n");
//				}
//			}	
			continue;// if light is shadowed the pass
		}
#endif
		H = (L -ray.dir)/2;// notice here
		H.normalize();     // remember to normalize, otherwise errors occur
		// else not shadowed
		float nDotL = record.normal * L;
		float nDotH = record.normal * H;
		diffuse += (*itr)->col * ( nDotL >0.0 ? nDotL : 0);
		specular += (*itr)->col * pow((nDotH > 0.0 ? nDotH : 0), mat.shiness);	
	}

	col += mat.diffuse * diffuse + mat.specular * specular;

	// recursive call
	Ray ref = Ray(record.pos, R);
	col1 = Radiance(ref, depth);
	// add the color
	col = col  + col1 * mat.specular;
	// clamp the color
	col.clamp();

	return col;
}



void Scene::buildBVH() {
    //if(mBVH) freeBVH(); 
    vector<Shape*>::iterator itr;
    for(itr = shapes.begin(); itr != shapes.end(); ++itr) {
        (*itr)->updateBoundingBox();
    }
    mBVH = new BVH(shapes);
}

