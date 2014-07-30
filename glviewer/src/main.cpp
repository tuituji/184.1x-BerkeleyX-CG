#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "vecmath.h"
#include <cassert>
#include "glviewer.h"

using namespace std;


GLViewer viewer;

unsigned int col_idx = 0;
int theta = 0;
bool start = false;
bool gMousePressed = false;
int interval = 100;
int list_id;
int gButton;

#define PI 3.14159265
void timeFunc(int t)
{
	if(start) {
	    theta += 5;
	    theta %= 360;	
	}
	glutPostRedisplay();
	glutTimerFunc(interval, timeFunc, 0);
}

// This function is called whenever a "Normal" key press is received.
void keyboardFunc( unsigned char key, int x, int y )
{
	switch ( key )
	{
	case 27: // Escape key
	    exit(0);
	    break;
	case 'c':
	    // add code to change color here
	    col_idx++;
		col_idx %= 4;
	    break;
	case 'r':
	    if(start) start = false;
	    else  start = true;
	    break;
	default:
	    cout << "Unhandled key press " << key << "." << endl;        
	}

	// this will refresh the screen so that the user sees the color change
	glutPostRedisplay();
}

GLfloat Lt0pos[] = {1.0f, 1.0f, 5.0f, 1.0f};
// This function is called whenever a "Special" key press is received.
// Right now, it's handling the arrow keys.
void specialFunc( int key, int x, int y )
{
	switch ( key )
	{
	case GLUT_KEY_UP:
	    // add code to change light position
	    Lt0pos[1] += 0.5;
		break;
	case GLUT_KEY_DOWN:
	    // add code to change light position
	    Lt0pos[1] -= 0.5;
		break;
	case GLUT_KEY_LEFT:
	    // add code to change light position
	    Lt0pos[0] -= 0.5;
		break;
	case GLUT_KEY_RIGHT:
	    // add code to change light position
	    Lt0pos[0] += 0.5;
		break;
	}
	// this will refresh the screen so that the user sees the light position
	glutPostRedisplay();
}

int     width, height;
int     startClickX, startClickY;
Matrix4f startRot;
Matrix4f currentRot;

void mouseFunc(int button, int state, int x, int y)
{
	startClickX = x;
	startClickY = y;
	gButton = button;

	if(state == GLUT_DOWN) {
		gMousePressed = true;	
		switch(button) {
		case GLUT_LEFT_BUTTON:
			currentRot = startRot;
			break;
		case GLUT_MIDDLE_BUTTON:
		case GLUT_RIGHT_BUTTON:
		default:
			break;
		}
	}
	else {
		startRot = currentRot;
		gMousePressed = false;
	}
//	glutPostRedisplay();
}

void arcBallRotation(int x, int y)
{
	float sx, sy, sz;
	float ex, ey, ez;
	float sl, el;
	float scale, dotp;

	sx = startClickX - width / 2.0;	// the center of the windows is origin 
	sy = startClickY - height / 2.0;	
	ex = x - width / 2.0;
	ey = y - height / 2.0;
	
	sy = -sy; // Y is up
	ey = -ey;

	scale = (float)(width > height ? height: width);
	scale = 1.0 / scale;
	
	sx *= scale;
	sy *= scale;
	ex *= scale;
	ey *= scale;
	
	sl = hypot(sx, sy);
	el = hypot(ex, ey);
	if(sl > 1.0) {
		sx /= sl;
		sy /= sl;
		sl = 1.0;
	}
	if(el > 1.0) {
		ex /= el;
		sy /= el;
		el = 1.0;
	}
	// project to a unit sphere;
	sz = sqrt(1.0 - sl * sl);
	ez = sqrt(1.0 - el * el);
	
	dotp = sx * ex + sy * ey + sz * ez;
	if(dotp !=  1) { // if parrallel
		Vector3f axis(sy * ez - ey * sz, sz * ex - ez * sx, sx * ey - ex * sy);
		axis.normalize();
		float angle =  acos(dotp);// why 2 ??
		currentRot = Matrix4f::rotation(axis, angle);
		currentRot = currentRot * startRot;
	}
	else {
		currentRot = startRot;
	}
}

void motionFunc(int x, int y)
{
	switch(gButton){
	case GLUT_LEFT_BUTTON:
		arcBallRotation(x, y);
		break;
	case GLUT_MIDDLE_BUTTON:
		break;
	case GLUT_RIGHT_BUTTON:
		break;
	default:
		break;	
	}
	glutPostRedisplay();
}


// This function is responsible for displaying the object.
void drawScene(void)
{

	// Clear the rendering window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Rotate the image
	glMatrixMode( GL_MODELVIEW );  // Current matrix affects objects positions
	glLoadIdentity();              // Initialize to the identity

#if 0
	gluLookAt(5.0 * sin(theta * PI/180), 0.0, 5.0 * cos(theta * PI/180),
	          0.0, 0.0, 0.0,
	          0.0, 1.0, 0.0);// we may rotate the camera or the object
#endif
	
	gluLookAt(viewer.cam_pos[0], viewer.cam_pos[1], viewer.cam_pos[2],
			viewer.cam_lookat[0], viewer.cam_lookat[1], viewer.cam_lookat[2],
			viewer.cam_up[0], viewer.cam_up[1], viewer.cam_up[2]);

	// Set material properties of object
//////////////////////////////////////////////////
// These are the default values for light 0
	// Here are some colors you might use - feel free to add more
	GLfloat diffColors[4][4] = { {0.5, 0.5, 0.9, 1.0},
	                             {0.9, 0.5, 0.5, 1.0},
	                             {0.5, 0.9, 0.3, 1.0},
	                             {0.3, 0.8, 0.9, 1.0} };
	
	// Here we use the first color entry as the diffuse color
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffColors[col_idx]);

	// Define specular color and shininess
	GLfloat specColor[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat shininess[] = {100.0};

	// Note that the specular color and shininess can stay constant
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  
	// Set light properties

	// Light color (RGBA)
	GLfloat Lt0diff[] = {1.0,1.0,1.0,1.0};
	// Light position

	glLightfv(GL_LIGHT0, GL_DIFFUSE, Lt0diff);
	glLightfv(GL_LIGHT0, GL_POSITION, Lt0pos);
// The above are default values, we will change it 
/////////////////////////////////////////////////////////

	glPushMatrix(); // push matrix here so will not disturbe the light position

	glMultMatrixf(currentRot); // here mult and rotate can not exchange
								// please check why ??
	glRotated(theta, 0, 1, 0); // we may rotate the object or the camera
	int id ;
	vector<Mesh*>& meshes = viewer.meshes;
	vector<Mesh*>::iterator mesh_itr;
	for(id = list_id, mesh_itr = meshes.begin(); mesh_itr != meshes.end(); 
			++mesh_itr, ++id){
		glPushMatrix();
		glMultMatrixf((*mesh_itr)->matrix);
	    glCallList(list_id);
		glPopMatrix();
	}

	GLUquadricObj* qobj=gluNewQuadric( );	
	vector<Sphere*>& spheres = viewer.spheres;
	vector<Sphere*>::iterator sphere_itr;
	for(sphere_itr= spheres.begin(); sphere_itr != spheres.end(); 
			++sphere_itr, ++id) {
  // seems of some problem omit it
/*
		Material &material = (*sphere_itr)->material;
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material.ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material.diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material.specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, material.shininess);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material.emission);
*/
		glPushMatrix();
		glMultMatrixf((*sphere_itr)->matrix);
		gluSphere(qobj, (*sphere_itr)->radius, 200, 200);
	//  glCallList(list_id);// error here
		glPopMatrix();
	}

	glPopMatrix();

	glutSwapBuffers();
}

// Initialize OpenGL's rendering modes
void initRendering()
{
	glEnable(GL_DEPTH_TEST);   // Depth testing must be turned on
	glEnable(GL_LIGHTING);     // Enable lighting calculations
	glEnable(GL_LIGHT0);
	// we may have more than one light
	for(vector<Light*>::iterator itr = viewer.lights.begin();
			itr != viewer.lights.end(); ++itr) {
//		glEnable((*itr)->id);  // seems some problems occur
	}

	list_id = glGenLists(viewer.meshes.size() + viewer.spheres.size());
	assert(list_id != 0);

	vector <Vector3f> & verts = viewer.verts;
	vector<Mesh*>& meshes = viewer.meshes;
	vector<Mesh*>::iterator mesh_itr;
	GLuint id = list_id;
	for(mesh_itr = meshes.begin(); mesh_itr != meshes.end(); ++mesh_itr, ++id) {
	    glNewList(id, GL_COMPILE);
// better to use vertex array
		vector<vector<unsigned> >& vecf = (*mesh_itr)->vecf;
	    vector<vector<unsigned> >::iterator itr;
		Vector3f normal;
  // seems some problems here
/*
		Material &material = (*mesh_itr)->material;
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material.ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material.diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material.specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, material.shininess);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material.emission);
*/
	    glBegin(GL_TRIANGLES);
	        for(itr = vecf.begin(); itr != vecf.end(); ++itr){
				normal = Vector3f::cross(verts[(*itr)[1]]-verts[(*itr)[0]],
								verts[(*itr)[2]] - verts[(*itr)[0]]);
				normal.normalize();
				glNormal3f(normal[0], normal[1], normal[2]);
				glVertex3f(verts[(*itr)[0]][0], verts[(*itr)[0]][1],
	                    verts[(*itr)[0]][2]);

				glNormal3f(normal[0], normal[1], normal[2]);
				glVertex3f(verts[(*itr)[1]][0], verts[(*itr)[1]][1],
						verts[(*itr)[1]][2]);

				glNormal3f(normal[0], normal[1], normal[2]);
				glVertex3f(verts[(*itr)[2]][0], verts[(*itr)[2]][1],
						verts[(*itr)[2]][2]);
	        }
	    glEnd();
		glEndList();
	}

	GLUquadricObj* qobj=gluNewQuadric( );	
	vector<Sphere*>& spheres = viewer.spheres;
	vector<Sphere*>::iterator sphere_itr;
	for(sphere_itr = spheres.begin(); sphere_itr != spheres.end(); 
		++sphere_itr, ++id){
		glNewList(id, GL_COMPILE);
			gluSphere(qobj, (*sphere_itr)->radius, 200, 200);
		glEndList();
	}
	
	startRot = Matrix4f::identity();
	currentRot = Matrix4f::identity();
}

// Called when the window is resized
// w, h - width and height of the window in pixels.
void reshapeFunc(int w, int h)
{
	// Always use the largest square viewport possible
	if (w > h) {
	    glViewport((w - h) / 2, 0, h, h);
	} else {
	    glViewport(0, (h - w) / 2, w, w);
	}

	width = w;
	height = h;
	// Set up a perspective view, with square aspect ratio
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// 50 degree fov, uniform aspect ratio, near = 1, far = 100
	gluPerspective(50.0, 1.0, 1.0, 100.0);
	//gluPerspective(viewer.cam_fovy, 1.0, 1.0, 100.0);
}


#define MAX_SIZE 256
void loadInput(char *input_file)
{
	// load the OBJ file here
	char buffer[MAX_SIZE];
	Material current_material;
	Mesh *current_mesh;
	viewer.input_file = string(input_file);
	viewer.output_file = viewer.input_file.substr(viewer.input_file.find_last_of("/") + 1) + ".ppm";

	Vector3f v;
	
	unsigned i0, i1, i2;
	ifstream in(viewer.input_file.c_str());
	string s, s_prev;
	GLuint light_id = GL_LIGHT0 + 1;
	while(in.getline(buffer, MAX_SIZE)) {
		string s;
		stringstream ss(buffer);
		ss >> s;
		if(s == "size"){
			ss >> viewer.width >> viewer.height;
		}
		else if(s == "camera") {
			ss >> v[0] >> v[1] >> v[2];
			viewer.cam_pos = v;
			ss >> v[0] >> v[1] >> v[2];
			viewer.cam_lookat = v;
			ss >> v[0] >> v[1] >> v[2];
			viewer.cam_up = v;
			ss >> viewer.cam_fovy;
		}
		else if(s == "diffuse") {
			ss >> current_material.diffuse[0]; 
			ss >> current_material.diffuse[1]; 
			ss >> current_material.diffuse[2]; 
		}
		else if(s == "ambient") {
			ss >> current_material.ambient[0];// notice ambient here;	
			ss >> current_material.ambient[1];// notice ambient here;	
			ss >> current_material.ambient[2];// notice ambient here;	
		}
		else if(s == "specular") {
			ss >> current_material.specular[0];
			ss >> current_material.specular[1];
			ss >> current_material.specular[2];
		}
		else if(s == "emission") {
			ss >> current_material.emission[0];
			ss >> current_material.emission[1];
			ss >> current_material.emission[2];
		}
		else if(s == "shininess") {
			ss >> current_material.shininess[0];
		}
		else if (s == "pushTransform") {
			viewer.mStack.push();
		}
		else if(s == "translate") {
			ss >> v[0] >> v[1] >> v[2];
			viewer.mStack.translate(v);
		}
		else if(s == "scale" ) {
			ss >> v[0] >> v[1] >> v[2];
			viewer.mStack.scale(v[0], v[1], v[2]);
		}
		else if(s == "rotate") {
			float angle;
			ss >> v[0] >> v[1] >> v[2] >> angle;
			viewer.mStack.rotate(v, angle);
		}
		else if(s == "popTransform") {
			viewer.mStack.pop();
		}
		else if(s == "maxverts") {
			ss >> viewer.maxverts;
		}
		else if(s == "vertex") {
			ss >> v[0] >> v[1] >> v[2];
			viewer.verts.push_back(v);
		}
		else if (s == "tri") { 
			vector<unsigned> tri;
			ss >> i0 >> i1 >> i2;
			tri.push_back(i0);
			tri.push_back(i1);
			tri.push_back(i2);
			
			if(s_prev != "tri") {
				current_mesh = new Mesh;
				current_mesh->material = current_material;
				current_mesh->matrix = viewer.mStack.top();
				viewer.meshes.push_back(current_mesh);
			}
			current_mesh->vecf.push_back(tri);
		}	
		else if(s == "sphere"){
			Sphere *sphere = new Sphere;
			ss >> v[0] >> v[1] >> v[2];
			sphere->center = v;
			ss >> sphere->radius;
			sphere->material = current_material;
			sphere->matrix = viewer.mStack.top();
			viewer.spheres.push_back(sphere);
		}
		else if(s == "point") {
			if(light_id < GL_MAX_LIGHTS -1) {
				PointLight *light = new PointLight;
				ss >> light->pos[0] >> light->pos[1] >> light->pos[2];
 				light->pos[3] = 1.0;
				ss >> light->col[0] >> light->col[1] >> light->col[2];
				viewer.lights.push_back(light);
				++light_id;
			}
		}
		else if(s == "directional") {
			if(light_id < GL_MAX_LIGHTS -1) {
				DirectionalLight *light = new DirectionalLight;
				ss >> light->dir[0] >> light->dir[1] >> light->dir[2];
				light->dir[3] = 0.0;
				ss >> light->col[0] >> light->col[1] >> light->col[2];
				viewer.lights.push_back(light);
				++light_id;
			}
		}
		else if(s == "") {  ;}
		else if(s[0] == '#') {  ; }
		else {
			cerr << s << " not implemented yet." << endl;
		}
		s_prev = s;
	}
	assert(viewer.maxverts == viewer.verts.size());
	return;
}

// Main routine.
// Set up OpenGL, define the callbacks and start the main loop
int main( int argc, char** argv )
{
	if(argc !=  2) {
		cerr << argv[0] << " <input_file>" << endl;
		return -1;
	}
  
	loadInput(argv[1]);

	glutInit(&argc,argv);

	// We're going to animate it, so double buffer 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

	// Initial parameters for window position and size
	glutInitWindowPosition( 60, 60 );
	glutInitWindowSize( viewer.width, viewer.height );
	glutCreateWindow("GL Viewer");

	// Initialize OpenGL parameters.
	initRendering();

	// Set up callback functions for key presses
	glutKeyboardFunc(keyboardFunc); // Handles "normal" ascii symbols
	glutSpecialFunc(specialFunc);   // Handles "special" keyboard keys

	 // Set up the callback function for resizing windows
	glutReshapeFunc( reshapeFunc );

	// Call this whenever window needs redrawing
	glutDisplayFunc( drawScene );
	// Start the main loop.  glutMainLoop never returns.
	glutTimerFunc(interval, timeFunc, 0);
	
	glutMouseFunc(mouseFunc);
	glutMotionFunc(motionFunc);

	glutMainLoop( );

	return 0;	// This line is never reached.
}
