#pragma once
#include <math.h>
#include <iostream>

#include "GL/glew.h"

class mat4x4
{
	public:
		mat4x4();
		mat4x4(GLfloat value);

		mat4x4(GLfloat m00, GLfloat m01, GLfloat m02, GLfloat m03,
			   GLfloat m10, GLfloat m11, GLfloat m12, GLfloat m13,
			   GLfloat m20, GLfloat m21, GLfloat m22, GLfloat m23,
			   GLfloat m30, GLfloat m31, GLfloat m32, GLfloat m33);
		~mat4x4();

    public:
		mat4x4 operator *(const mat4x4& b)const;

		friend std::ostream& operator << (std::ostream& out, const mat4x4& v)
		{
			return (out << v.mat[0] << ", " << v.mat[4] << ", " << v.mat[8] << ", "  <<  v.mat[12] << std::endl
						<< v.mat[1] << ", " << v.mat[5] << ", " << v.mat[9] << ", "  <<  v.mat[13] << std::endl
						<< v.mat[2] << ", " << v.mat[6] << ", " << v.mat[10] << ", " <<  v.mat[14] << std::endl
						<< v.mat[3] << ", " << v.mat[7] << ", " << v.mat[11] << ", " <<  v.mat[15] << std::endl);
		}
	public:
		GLfloat mat[16];
};

