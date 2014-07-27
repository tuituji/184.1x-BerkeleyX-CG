
#include "mesh.h"

bool Triangle::intersect(const Ray &r, HitRecord &record)
{
#define X 0
#define Y 1
#define Z 2

	float tval;
	float eps = 1e-4;
	Vec3f *p = mesh_ptr->verts;

	float A = p[idx[0]][X] - p[idx[1]][X];
	float B = p[idx[0]][Y] - p[idx[1]][Y];
	float C = p[idx[0]][Z] - p[idx[1]][Z];

	float D = p[idx[0]][X] - p[idx[2]][X];
	float E = p[idx[0]][Y] - p[idx[2]][Y];
	float F = p[idx[0]][Z] - p[idx[2]][Z];
	
	float G = r.dir.x;
	float H = r.dir.y;
	float I = r.dir.z;
	
	float J = p[idx[0]][X] - r.pos.x;
	float K = p[idx[0]][Y] - r.pos.y;
	float L = p[idx[0]][Z] - r.pos.z;

	float EIHF = E*I - H*F;
	float GFDI = G*F - D*I;
	float DHEG = D*H - E*G;	
	
	float denom = A * EIHF + B * GFDI + C * DHEG;
	if(denom == 0.0) return false;
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

	Vector normal;
	normal = cross(
			Vector(p[idx[2]][X]- p[idx[0]][X], p[idx[2]][Y]- p[idx[0]][Y],
				p[idx[2]][Z]- p[idx[0]][Z]),
			Vector(p[idx[1]][X]- p[idx[0]][X], p[idx[1]][Y]- p[idx[0]][Y],
				p[idx[1]][Z]- p[idx[0]][Z]));

	normal.normalize();
//	if(normal * r.dir > 0) normal = - normal;// is it true ??
	record.normal = - normal;
	record.obj = this;  // please check it
	record.pos = Point(r.pos + record.t * r.dir);

	return true;
#undef x
#undef y
#undef z
}

void Triangle::updateBoundingBox()
{
	const float epsilon = 0.00001f;
	Vector min, max;
	Vector p0(mesh_ptr->verts[idx[0]]);
	Vector p1(mesh_ptr->verts[idx[1]]);
	Vector p2(mesh_ptr->verts[idx[2]]);

	min.x = p0.x < p1.x ? p0.x : p1.x;
	min.y = p0.y < p1.y ? p0.y : p1.y;
	min.z = p0.z < p1.z ? p0.z : p1.z;
	min.x = min.x < p2.x ? min.x : p2.x;
	min.y = min.y < p2.y ? min.y : p2.y;
	min.z = min.z < p2.z ? min.z : p2.z;

	max.x = p0.x > p1.x ? p0.x : p1.x;
	max.y = p0.y > p1.y ? p0.y : p1.y;
	max.z = p0.z > p1.z ? p0.z : p1.z;
	max.x = max.x > p2.x ? max.x : p2.x;
	max.y = max.y > p2.y ? max.y : p2.y;
	max.z = max.z > p2.z ? max.z : p2.z;

	min.x -= epsilon;
	min.y -= epsilon;
	min.z -= epsilon;

	max.x += epsilon;
	max.y += epsilon;
	max.z += epsilon;

	bbox = BBox(min, max);
}


#if 0
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
		record.pos = Point(ray.pos + t * ray.dir);
		return true;
	}
	return false;
}
#endif
