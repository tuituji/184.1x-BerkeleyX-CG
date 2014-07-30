#include <cstdlib>
#include <cstdio>
#include <string>

#include "vecmath.h"
#include "MatrixStack.h"

using namespace std;


class Material {
public:
	float diffuse[3];
	float ambient[3];
	float specular[3];
	float emission[3];
	float shininess[1];
};

class Sphere {
public:
	float radius;
	Vector3f center;
	Material material;
	Matrix4f matrix;
};



class Mesh {
public:
	vector<vector<unsigned> > vecf;
	Material material;
	Matrix4f matrix;
};


class Light {
public:
	float col[3];
	int id;
	virtual void setLightParameter() = 0;
};

class PointLight : public Light {
public:
	Vector4f pos;
	void setLightParameter();
};

class DirectionalLight : public Light {
public:
	Vector4f dir;
	void setLightParameter();
};

class GLViewer {
public:
	string input_file;
	string output_file;
	vector <Vector3f> verts;
	size_t maxverts;
	vector<Mesh*> meshes;
	vector<Sphere*> spheres;

	vector <Light*> lights;
	int width, height;

	Vector3f cam_pos;
	Vector3f cam_lookat;
	Vector3f cam_up;
	float cam_fovy;
	MatrixStack mStack;
};

