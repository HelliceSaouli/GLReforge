#pragma once

#include <math.h>
#include <iostream>

#include "GL/glew.h"

#include "vec3.h"

class quaternion
{
	public:
		quaternion(GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _w);
		quaternion();
		~quaternion();
	
	public:
		void normalize();

		GLfloat length();

		quaternion conjugate()const;
		quaternion operator *(const quaternion& b)const;
		quaternion operator *(const vec3& b)const;

		friend std::ostream& operator << (std::ostream& out, const quaternion& v)
		{
			return (out << " q(" << v.x << ", " << v.y << ", " << v.z << ", "<< v.w << ")" << std::endl);
		}

	public:
		GLfloat x;
		GLfloat y;
		GLfloat z;
		GLfloat w;
};

