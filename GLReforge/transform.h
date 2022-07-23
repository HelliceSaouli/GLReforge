#pragma once

#include "vec3.h"
#include "quaternion.h"
#include "mat4x4.h"

#include "GL/glew.h"

class transform
{
	public:
		transform();
		~transform();

	public:
		/* move object according to x, y and z*/
		mat4x4 compute_translate(GLfloat x, GLfloat y, GLfloat z)const;
		void   translate(GLfloat x, GLfloat y, GLfloat z);
		/* rotate according to xyz, the angles input are in degree*/
		mat4x4 compute_rotation(GLfloat xangle, GLfloat yangle, GLfloat zangle)const;
		void rotation(GLfloat xangle, GLfloat yangle, GLfloat zangle);
		/* scale according to xyz*/
		mat4x4 compute_scale(GLfloat x, GLfloat y, GLfloat z)const;
		void scale(GLfloat x, GLfloat y, GLfloat z);

		/* get world transfrom, or local ?*/
		vec3 get_location()const;
		vec3 get_scale()const;
		mat4x4  get_rotator()const;
	private:
		mat4x4 translate_matrix;
		mat4x4 scale_matrix;
		mat4x4 rotate_matrix;
};

