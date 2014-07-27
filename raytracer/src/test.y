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

int num_tri = 0;

extern int yylex(void);
void  yyerror(string s);


Material current_material;
//Shape *current_shape;
Mesh * current_mesh = NULL;

%}
 /* declare tokens */

%union {
	float num;
	char str[512];
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
%token REFLECT
%token PLANE
%token POP
%token PUSH
%token SCALE
%token TRANSLATE
%token ROTATE
%token EMISSION
%token OUTPUT
%token MAXDEPTH
%token <str> OUTFILE
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
//	printf("size %f %f\n", $2, $3);
}
| CAMERA NUM NUM NUM NUM NUM NUM NUM NUM NUM NUM 
{
	Camera *cam = new Camera(Point($2, $3, $4), Point($5, $6, $7),	
				Vector($8, $9, $10), $11, 
				raytracer->width, raytracer->height);
	raytracer->camera = cam;
}
|OUTPUT OUTFILE
{

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
| MAXDEPTH NUM
{
	raytracer->maxdepth = $2;
}
| POINT NUM NUM NUM NUM NUM NUM
{
	Type t = PointLIGHT;
	Light* l = new PointLight(t, Point($2, $3, $4), Color($5, $6, $7));
	raytracer->scene->lights.push_back(l);
}
| EMISSION NUM NUM NUM
{
	current_material.emission = Color($2, $3, $4);
}
| DIFFUSE NUM NUM NUM 
{
	current_material.diffuse = Color($2, $3, $4);
}
| SHINESS NUM 
{
	current_material.shiness = $2;
	//current_material.shiness = 100;
}
| SPECULAR NUM NUM NUM
{
	current_material.specular = Color($2, $3, $4);
}
| REFLECT NUM NUM NUM
{
	current_material.reflect = Color($2, $3, $4);
}
|POP
{
	MatrixStack& tStack = raytracer->transStack;
	tStack.Pop();
}
| PUSH
{
	MatrixStack& tStack = raytracer->transStack;
	tStack.Push();
}
| TRANSLATE NUM NUM NUM
{
	MatrixStack& tStack = raytracer->transStack;
	tStack.Translate($2, $3, $4);
}
| SCALE NUM NUM NUM
{
//	printf("error scale\n");
	MatrixStack& tStack = raytracer->transStack;
	tStack.Scale($2, $3, $4);
}
| ROTATE NUM NUM NUM NUM
{
	printf("error rotate\n");
	MatrixStack& tStack = raytracer->transStack;
	tStack.Rotate($2, $3, $4, $5);
}
| SPHERE NUM NUM NUM NUM
{
	MatrixStack& tStack = raytracer->transStack;
	Sphere *s = new Sphere(Vector($2, $3, $4), $5);
	s->center = tStack.Top() * s->center; 
// just translate sphere
// we ignore other type of transformation
	s->material = current_material;
	raytracer->scene->addShape(s);

//	s->setMatrix(tStack.Top());
}
| PLANE NUM NUM NUM NUM
{
	Plane *plane = new Plane(Vector($2, $3, $4), $5);
	plane->material = current_material;
	raytracer->scene->addShape(plane);
}
| MAXVERTS NUM
{
	raytracer->scene->num_verts = $2;
	raytracer->scene->verts = new Vec3f[raytracer->scene->num_verts];
}
| VERTEX NUM NUM NUM
{
	if(i >= raytracer->scene->num_verts) {
		fprintf(stderr, "Error number of vertex\n");
	}
	raytracer->scene->verts[i][0] = $2;
	raytracer->scene->verts[i][1] = $3;
	raytracer->scene->verts[i][2] = $4;
	++i;
}
|tri_list
{
	// finish reading all tri
//	MatrixStack& tStack = raytracer->transStack;
	current_mesh->material =  current_material;
//	current_mesh->setMatrix(tStack.Top());
//	raytracer->scene->addShape(current_mesh);
	int j = 0;
	Vec3f* verts = raytracer->scene->verts;
	MatrixStack& tStack = raytracer->transStack;
	for(j = 0; j  < current_mesh->num_verts; ++j) {
		Point p(verts[j][0], verts[j][1], verts[j][2]);
		p = tStack.Top() * p;
		current_mesh->verts[j][0] = p.x;
		current_mesh->verts[j][1] = p.y;
		current_mesh->verts[j][2] = p.z;
	}
	current_mesh = NULL;
//	printf("finish processing tri list\n");
}

tri_list: tri_list TRI NUM NUM NUM
{
//	if((++num_tri)% 1000 == 0)	printf("tris; %d\n", num_tri);
	if(current_mesh == NULL) current_mesh = new Mesh(raytracer->scene);
	raytracer->scene->addShape(new Triangle($3, $4, $5, current_mesh));	
}
| TRI NUM NUM NUM
{
	if(current_mesh == NULL) current_mesh = new Mesh(raytracer->scene);
//	current_mesh->addTriangle(new Triangle($2, $3, $4));
	raytracer->scene->addShape(new Triangle($2, $3, $4, current_mesh));
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
