#include "MatrixStack.h"
#include <iostream>
#include <cstdio>

using namespace std;

MatrixStack::MatrixStack()
{
	// Initialize the matrix stack with the identity matrix.
	m_matrices.push_back(Matrix4f::identity());
}

void MatrixStack::clear()
{
	// Revert to just containing the identity matrix.
	m_matrices.clear();
	m_matrices.push_back(Matrix4f::identity());
}

Matrix4f MatrixStack::top()
{
	// Return the top of the stack
	Matrix4f mat = m_matrices.back();
	return mat;
}

void MatrixStack::push()
{
	// Push m onto the stack.
	// Your stack should have OpenGL semantics:
	// the new top should be the old top multiplied by m
	m_matrices.push_back(m_matrices.back());
	
}

void MatrixStack::pop()
{
	// Remove the top element from the stack
	if(m_matrices.size() == 1) {
		cerr << "error stack size is 1 now" << endl;
	}
	m_matrices.pop_back();
}

void MatrixStack::translate(float x, float y, float z)
{
	Matrix4f mat = Matrix4f::translation(x, y, z);
	m_matrices.back() *= mat;
}

void MatrixStack::translate(const Vector3f &v)
{
	Matrix4f mat = Matrix4f::translation(v);
	m_matrices.back() *= mat;
}

void MatrixStack::scale(float sx, float sy, float sz)
{
	Matrix4f mat = Matrix4f::scaling(sx, sy, sz);
	m_matrices.back() *= mat;
}

#define PI 3.141592653589793
#define deg2rad(x) (x*PI/180)
void MatrixStack::rotate(const Vector3f& dir, float degree)
{
	Matrix4f mat;
	float radiance = deg2rad(degree);
	if(dir.x() != 0 && dir.y() == 0 && dir.z() == 0){
		mat = Matrix4f::rotateX(radiance);
	}
	else if(dir.x() == 0 && dir.y() != 0 && dir.z() == 0){
		mat = Matrix4f::rotateY(radiance);
	}
	else if(dir.x() == 0 && dir.y() == 0 && dir.z() != 0){
		mat = Matrix4f::rotateZ(radiance);
	}
	else {
		mat = Matrix4f::rotation(dir, radiance);
	}
	m_matrices.back() *= mat;
}
