// Transform.cpp: implementation of the Transform class.


#include "Transform.h"

#include <cstdio>
//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  // YOUR CODE FOR HW1 HERE
	glm::mat4 ViewRotate = glm::rotate(glm::mat4(), degrees, axis);
  // You will change this return call
	return mat3(ViewRotate);
//  return mat3();
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE
	
//	printf("come to left");
//	fflush(stdout);
	glm::mat3 mat = rotate((-1) * degrees,  glm::normalize(up));
	eye = mat * eye;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
  // YOUR CODE FOR HW1 HERE 
	glm::vec3 vec = glm::cross( up, eye);
	glm::mat3 mat = rotate((1) * degrees, glm::normalize(vec));
	eye = mat * eye;
	up = glm::cross(eye, vec);
	up = glm::normalize(up);
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  // YOUR CODE FOR HW1 HERE
	vec3 forward = glm::normalize(-eye);
	vec3 side = glm::normalize(glm::cross(forward, up));
	up = glm::cross(side, forward);
	glm::mat4 mat(1);

	mat[0][0] = side[0];
	mat[1][0] = side[1];
	mat[2][0] = side[2];
	
	mat[0][1] = up[0];
	mat[1][1] = up[1];
	mat[2][1] = up[2];
	
	mat[0][2] = -forward[0];
	mat[1][2] = -forward[1];
	mat[2][2] = -forward[2];

  // You will change this return call
  return mat4(glm::translate(mat, -eye));
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
