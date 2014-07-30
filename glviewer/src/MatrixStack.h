#ifndef MATRIX_STACK_H
#define MATRIX_STACK_H

#include <vector>
#include "vecmath.h"


class MatrixStack
{
public:
	MatrixStack();
	void clear();
	Matrix4f top();
	void push();
	void pop();
	void translate(float x, float y, float z);
	void translate(const Vector3f& v);
	void scale(float sx, float sy, float sz);
	void rotate(const Vector3f& dir, float radians);

private:

	std::vector< Matrix4f > m_matrices;

};

#endif // MATRIX_STACK_H
