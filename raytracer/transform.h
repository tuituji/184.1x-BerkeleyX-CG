#ifndef _TRANSFORM_H
#define _TRANSFORM_H

class Matrix {

public:
	float mat[4][4];

};


class Transformation {
public: 
	Matrix m, m_inv;

}

#endif
