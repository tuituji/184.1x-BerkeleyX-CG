#ifndef _LIGHT_H
#define _LIGHT_H

#include "material.h"
#include "geometry.h"

enum Type { PointLIGHT,  DirectionalLIGHT };

class Light {
public:
	Light(Type t,const Color& c): type(t), col(c) { };
	virtual Vector getDir(const Point &p) =  0;
	Type type;
	Color col;
};

class PointLight: public Light {
public:
	PointLight(Type t, Point p, Color c) : Light(t, c), pos(p) {  };
	
	inline Vector getDir(const Point& p) {
		Vector v = Vector(p - pos);
		v.normalize();
		return v;
	}

	Point pos;
};

class DirectionalLight : public Light {
public:
	DirectionalLight(Type t, Vector v, Color c): Light(t, c), dir(v) {
		dir.normalize();
	};
	
	inline Vector getDir(const Point& p) {
		return dir;
	}

	Vector dir;
};


#endif
