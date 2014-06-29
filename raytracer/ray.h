#ifndef _RAY_H
#define _RAY_H


#include "geometry.h"


class Ray {
public:
    Ray() : pos(), dir(){ } ;
    Ray(const Point &p, const Vector &d): pos(p), dir(d) {
		dir.normalize();
	}

    Point pos;
    Vector dir;
    float t_min, t_mx;

	
};



#endif
