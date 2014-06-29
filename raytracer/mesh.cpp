
#include "mesh.h"

bool Triangle::intersect(const Ray &r, HitRecord &record)
{
	float tval;
	float eps = 1e-4;
	Point *p = mesh_ptr->scene_ptr->vertexs;

	float A = p[idx[0]].x - p[idx[1]].x;
	float B = p[idx[0]].y - p[idx[1]].y;
	float C = p[idx[0]].z - p[idx[1]].z;

	float D = p[idx[0]].x - p[idx[2]].x;
	float E = p[idx[0]].y - p[idx[2]].y;
	float F = p[idx[0]].z - p[idx[2]].z;
	
	float G = r.dir.x;
	float H = r.dir.y;
	float I = r.dir.z;
	
	float J = p[idx[0]].x - r.pos.x;
	float K = p[idx[0]].y - r.pos.y;
	float L = p[idx[0]].z - r.pos.z;

	float EIHF = E*I - H*F;
	float GFDI = G*F - D*I;
	float DHEG = D*H - E*G;	
	
	float denom = A * EIHF + B * GFDI + C * DHEG;
	float beta = (J * EIHF + K * GFDI + L * DHEG) / denom;
	if(beta <= 0.0f || beta >= 1.0f) return false;

	float AKJB = A*K - J*B;
	float JCAL = J*C - A*L;
	float BLKC = B*L - K*C;
	
	float gamma = (I*AKJB + H *JCAL + G*BLKC)/denom;
	if(gamma <= 0.0f || (beta + gamma) >= 1.0f) return false;

	tval = -(F*AKJB + E*JCAL + D*BLKC)/denom;
	if(tval < eps) return false;

	record.t = tval;
	
	Vector normal = cross(Vector(p[idx[0]]- p[idx[1]]), 
							Vector(p[idx[0]]- p[idx[2]]));
	normal.normalize();
	if(normal * r.dir > 0) normal = - normal;
	record.normal = normal;
	return true;
}

bool Mesh::intersect(const Ray& ray, HitRecord& record)
{
	float inf = 1e20;
	float t = inf;

	vector<Triangle*>::iterator itr;
	for(itr = tris.begin(); itr != tris.end(); ++itr) {
		if((*itr)->intersect(ray, record) && record.t < t) {
			t = record.t;
		}
	}
	if (t < inf) {
		record.obj = this;
		record.t = t;
		return true;
	}
	return false;
}


