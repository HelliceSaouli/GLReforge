#pragma once
#include <math.h>
#include <iostream>

#include "GL/glew.h"
/* vector 3 math */

class vec3
{
	public:
		vec3();
		vec3(GLfloat _x, GLfloat _y, GLfloat _z);
		~vec3();

	public:
		vec3 operator *(const GLfloat v)const;
		vec3 operator /(const GLfloat v)const;
		vec3 operator +(const GLfloat v)const;
		vec3 operator -(const GLfloat v)const;

		vec3 operator *(const vec3& v)const;
		vec3 operator +(const vec3& v)const;
		vec3 operator -(const vec3& v)const;
		
		friend std::ostream& operator << (std::ostream& out, const vec3& v)
		{
			return (out << " v(" << v.x << ", " << v.y << ", " << v.z << ")"<< std::endl);
		}

	public:
		void negative(); /* remove this later */
		void normalize();

		GLfloat length();
		GLfloat length_square();
		GLfloat dot_product(const vec3& b)const;

		vec3 cross(const vec3& v)const;
		vec3 rotate(GLfloat angleinradiant, const vec3& axis)const;


	public:
		GLfloat x;
		GLfloat y;
		GLfloat z;
};

