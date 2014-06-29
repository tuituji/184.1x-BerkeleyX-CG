
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stack>
//#include "params.h"
#include "raytracer.h"
#include "geometry.h"

extern int yyparse(void);
extern FILE *yyin;
//extern int yydebug;


RayTracer *raytracer;
int maxvertex  = 0;

int main(int argc, char **argv)
{
	char filename[16];

	if(argc != 2) {
		fprintf(stderr, "%s <filename>\n", argv[0]);
		return -1;
	}

	raytracer = new RayTracer;
	
//	if (getenv("PBRT_YYDEBUG") != NULL)
//		yydebug = 1;
	
	memcpy(filename, argv[1], 16);
	yyin = fopen(filename, "r");

	if(yyin != NULL) {
		yyparse();
	}
	fclose(yyin);	

	raytracer->trace();		

	return 0;
}

