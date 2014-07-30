#include "glviewer.h"
#include <GL/glut.h>


void DirectionalLight :: setLightParameter()
{
	GLfloat mat_ambient[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_specular[] =  {1.0, 1.0, 1.0, 1.0};
	glLightfv(id, GL_AMBIENT, mat_ambient);	
	glLightfv(id, GL_DIFFUSE, mat_diffuse);
	glLightfv(id, GL_SPECULAR, mat_specular);
    glLightfv(id, GL_POSITION, dir);
}


void PointLight ::setLightParameter()
{
	GLfloat mat_ambient[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_specular[] =  {1.0, 1.0, 1.0, 1.0};
	glLightfv(id, GL_AMBIENT, mat_ambient);	
	glLightfv(id, GL_DIFFUSE, mat_diffuse);
	glLightfv(id, GL_SPECULAR, mat_specular);
    glLightfv(id, GL_POSITION, pos);
}
