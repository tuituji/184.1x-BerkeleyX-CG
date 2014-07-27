#include "geometry.h"

void MatrixStack::Push()
{
	Matrix4x4 top = mStack.top();
	mStack.push(top);
}

void MatrixStack::Translate(float x, float y, float z) 
{	
	Matrix4x4 m;
	// unlike matlab , here we use the row main matrix
	
//	m[3][0] = x;
//    m[3][1] = y;
//    m[3][2] = z;
	
	m[0][3] = x;
	m[1][3] = y;
	m[2][3] = z;
	mStack.top() *= m;
		
}

void MatrixStack::Scale(float x, float y, float z)
{
	Matrix4x4 m;
	m[0][0] = x;
	m[1][1] = y;
	m[2][2] = z;
	mStack.top() *= m;
}


void MatrixStack::Rotate(float x, float y, float z, float alpha)
{
	Matrix4x4 m;// m is now an identity matrix
//  To set rotate matrix
	
	float cos_alpha = cos(deg2rad(alpha));
	float sin_alpha = sin(deg2rad(alpha));

	if(x != 0.0 && y == 0.0 && z == 0.0) {  // rotate according to x axis
		m.mat[1][1] = cos_alpha;
		m.mat[1][2] = -sin_alpha;
		m.mat[2][1] = sin_alpha;
		m.mat[2][2] = cos_alpha;
	}
	else if(x == 0.0 && y != 0.0 && z == 0.0) { // rotate according to y axis
		m.mat[0][0]	= cos_alpha;
		m.mat[0][2] = sin_alpha;
		m.mat[2][0] = -sin_alpha;
		m.mat[2][2] = cos_alpha;
	}
	else if(x == 0.0 && y == 0.0 && z != 0.0) {
		m.mat[1][1] = cos_alpha;
		m.mat[1][2] = -sin_alpha;
		m.mat[2][1] = sin_alpha;
		m.mat[2][2] = cos_alpha;
	}
	else {
		Vector axis = Vector(x, y, z)	;
		axis.normalize();
		x = axis.x;
		y = axis.y;
		z = axis.z;
	
		m.mat[0][0] = (1 - cos_alpha) * x * x + cos_alpha;
		m.mat[0][1] = (1 - cos_alpha) * x * y - sin_alpha * y;
		m.mat[0][2] = (1 - cos_alpha) * x * z + sin_alpha * y;
		
		m.mat[1][0] = (1 - cos_alpha) * x * y + sin_alpha * z;
		m.mat[1][1] = (1 - cos_alpha) * y * y + cos_alpha;
		m.mat[1][2] = (1 - cos_alpha) * y * z - sin_alpha * x;

		m.mat[2][0] = (1 - cos_alpha) * x * z - sin_alpha * y;
		m.mat[2][1] = (1 - cos_alpha) * y * z + sin_alpha * x;
		m.mat[2][2] = (1 - cos_alpha) * z * z + cos_alpha;
	}
	mStack.top() *= m;
}

