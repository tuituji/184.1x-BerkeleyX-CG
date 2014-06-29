#ifndef _CAMERA_H
#define _CAMERA_H

#include "ray.h"
#include "geometry.h"

class Camera {
public:
//	Camera():cam_pos(), cam_dir(), cam_up(), 
//		cam_fovy(0.0), uvw() { };
	
//	Camera(Vector &p, Vector &d, Vector &u, float f):
//		cam_pos(p), cam_dir(d), cam_up(u), cam_fovy(f) { }; 
	Camera(Point p, Point lookat , Vector u, float f, int width, int height):
		cam_pos(p), cam_dir(lookat - p), cam_up(u), cam_fovy(f), uvw() { 

		cam_dir.normalize();
		cam_up.normalize();
		distance = height/ 2 * tanf (deg2rad(90 - cam_fovy));
		u0 = -width / 2.0;
		v0 = -height/ 2.0;
		u1 =  width / 2.0;
		v1 =  height/ 2.0;
	
//		float t = distance/sqrt(cam_dir.lengthSquared());
//		center = Point(cam_pos + t * cam_dir);
		center = cam_pos;
		uvw.initFromWV(-cam_dir, cam_up);
		corner = center + uvw.u()*u0 + uvw.v()*v0 - uvw.w() * distance;
		// the left bootom of the view plane;
		across = uvw.u() * (u1 - u0);  // should be u1 - u0 ??
		up = uvw.v() * (v1 - v0);  // up here should be the same as cam_up ??
	}; 

	Ray generateRay(float a, float b);
	Point cam_pos;
	Vector cam_dir;
	Vector cam_up;
	float cam_fovy;

	ONB uvw;
	Point center; // should be in world coordinate
	Point corner; // should be in world coordinate
	Vector across;
	Vector up;

	float u0, u1, v0, v1;
	float distance;
};

#endif
