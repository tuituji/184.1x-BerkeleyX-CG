/* simplest version of calculator */
%{
#include <cstdio>
#include <string>
#include <stack>
#include "scene.h"
#include "camera.h"
#include "geometry.h"
#include "raytracer.h"
#include "material.h"
#include "shape.h"
#include "primitive.h"
#include "mesh.h"

using namespace std;

extern struct Params* parameters;
extern RayTracer *raytracer;
extern int maxvertx ;

int i = 0;


extern int yylex(void);
void  yyerror(string s);


Material current_material;
//Shape *current_shape;
Mesh * current_mesh = NULL;

%}
 /* declare tokens */

%union {
	float num;
	char str[16];
}

%token SIZE
%token CAMERA
%token AMBIENT
%token DIRECTIONAL
%token POINT
%token DIFFUSE
%token SPECULAR
%token MAXVERTS
%token VERTEX
%token TRI
%token SPHERE
%token SHINESS
%token PLANE
%token POP
%token PUSH
%token SCALE
%token TRANSLATE
%token <num> NUM

%%

param_stmt_list: param_stmt_list param_stmt { }
    | param_stmt { };

param_stmt : SIZE NUM NUM
{
	Film f((int)$2, (int)$3);
	raytracer->film = f;
	raytracer->width = (int)$2;
	raytracer->height = (int)$3;
	printf("size %f %f\n", $2, $3);
}
| CAMERA NUM NUM NUM NUM NUM NUM NUM NUM NUM NUM 
{
	Camera *cam = new Camera(Point($2, $3, $4), Point($5, $6, $7),	
				Vector($8, $9, $10), $11, 
				raytracer->width, raytracer->height);
	raytracer->camera = cam;
}
| AMBIENT NUM NUM NUM
{
	current_material.ambient = Color($2, $3, $4);
}
| DIRECTIONAL NUM NUM NUM NUM NUM NUM
{
	Type t = DirectionalLIGHT;
	Light* l = new DirectionalLight(t, Vector($2, $3, $4),Color($5, $6, $7));
	raytracer->scene->lights.push_back(l);
}
| POINT NUM NUM NUM NUM NUM NUM
{
	Type t = PointLIGHT;
	Light* l = new PointLight(t, Point($2, $3, $4), Color($5, $6, $7));
	raytracer->scene->lights.push_back(l);
}
| DIFFUSE NUM NUM NUM 
{
	current_material.diffuse = Color($2, $3, $4);
}
| SHINESS NUM 
{
	current_material.shiness = $2;
}
| SPECULAR NUM NUM NUM
{
	current_material.specular = Color($2, $3, $4);
}

|POP
{
	stack<Matrix4x4> & tStack = raytracer->transStack;
	tStack.pop();
}

| PUSH
{
	stack<Matrix4x4> & tStack = raytracer->transStack;
	tStack.push(tStack.top());
}
| TRANSLATE NUM NUM NUM
{
	Matrix4x4 m;
	Matrix4x4& m0 = raytracer->transStack.top();
	m[3][0] = $2;
	m[3][1] = $2;
	m[3][2] = $4;
	m0 *= m;// m0 is the reference to the top of the stack
}
|SCALE NUM NUM NUM
{
	Matrix4x4 m;
	stack<Matrix4x4> & tStack = raytracer->transStack;
	m[0][0]	= $2;
	m[1][1] = $3;
	m[2][2] = $4;
	tStack.top() *= m;
}
| SPHERE NUM NUM NUM NUM
{
	stack<Matrix4x4> & tStack = raytracer->transStack;
	Sphere *s = new Sphere(Vector($2, $3, $4), $5);
	s->setMaterial(current_material);
	raytracer->scene->addShape(s);
	s->setMatrix(tStack.top());
}
| PLANE NUM NUM NUM NUM
{
	Plane *plane = new Plane(Vector($2, $3, $4), $5);
	plane->setMaterial(current_material);
	raytracer->scene->addShape(plane);
}
| MAXVERTS NUM
{
	raytracer->scene->num_vertex = $2;
	raytracer->scene->vertexs = new Point[raytracer->scene->num_vertex];
}
| VERTEX NUM NUM NUM
{
	if(i >= raytracer->scene->num_vertex) {
		fprintf(stderr, "Error number of vertex\n");
	}
	raytracer->scene->vertexs[i++]  = Point($2, $3, $4);
}
|tri_list
{
	// finish reading all tri
	current_mesh->setMaterial(current_material);
	raytracer->scene->addShape(current_mesh);
	current_mesh = NULL;
}

tri_list: tri_list TRI NUM NUM NUM
{
	if(current_mesh == NULL) current_mesh = new Mesh(raytracer->scene);
	current_mesh->addTriangle(new Triangle($3, $4, $5));	
}
| TRI NUM NUM NUM
{
	if(current_mesh == NULL) current_mesh = new Mesh(raytracer->scene);
	current_mesh->addTriangle(new Triangle($2, $3, $4));
}



%%

#if 0
main(int argc, char **argv)
{
    yyparse();
}
#endif


void  yyerror(string s)
{
    fprintf(stderr, "error: %s\n", s.c_str());
}
