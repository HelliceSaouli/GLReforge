#include "defines.h"
#include "transform.h"

transform::transform() {
	/* in the center of every thing*/
	translate_matrix = compute_translate(0.0f, 0.0f, 0.0f);
	rotate_matrix    = compute_rotation(0.0f, 0.0f, 0.0f);
	scale_matrix     = compute_scale(1.0f, 1.0f, 1.0f);
}

transform::~transform() {

}

mat4x4 transform::compute_translate(GLfloat x, GLfloat y, GLfloat z)const{
	mat4x4 translation_matrix;
	translation_matrix.mat[12] = x;
	translation_matrix.mat[13] = y;
	translation_matrix.mat[14] = z;

	return translation_matrix;
}

void transform::translate(GLfloat x, GLfloat y, GLfloat z){
	translate_matrix = compute_translate(x, y, z);
}

/* I will change to quaternion later*/
mat4x4 transform::compute_rotation(GLfloat xangle, GLfloat yangle, GLfloat zangle)const {
	mat4x4 xrotation;
	mat4x4 yrotation;
	mat4x4 zrotation;

	GLfloat xangleradiant = (GLfloat)(xangle * TORADIEN);
	xrotation.mat[5] = (GLfloat)cos(xangleradiant);
	xrotation.mat[9] = (GLfloat)-sin(xangleradiant);
	xrotation.mat[6] = (GLfloat)sin(xangleradiant);
	xrotation.mat[10] = (GLfloat)cos(xangleradiant);

	GLfloat yangleradiant = (GLfloat)(yangle * TORADIEN);
	yrotation.mat[0] = (GLfloat)cos(yangleradiant);
	yrotation.mat[8] = (GLfloat)-sin(yangleradiant);
	yrotation.mat[2] = (GLfloat)sin(yangleradiant);
	yrotation.mat[10] = (GLfloat)cos(yangleradiant);

	GLfloat zangleradiant = (GLfloat)(zangle * TORADIEN);
	zrotation.mat[0] = (GLfloat)cos(zangleradiant);
	zrotation.mat[4] = (GLfloat)sin(zangleradiant);
	zrotation.mat[1] = (GLfloat)-sin(zangleradiant);
	zrotation.mat[5] = (GLfloat)cos(zangleradiant);

	return zrotation * yrotation * xrotation;
}

void transform::rotation(GLfloat xangle, GLfloat yangle, GLfloat zangle){
	rotate_matrix = compute_rotation(xangle, yangle, zangle);
}

mat4x4 transform::compute_scale(GLfloat x, GLfloat y, GLfloat z)const {
	mat4x4 scale_matrix;
	scale_matrix.mat[0] = x;
	scale_matrix.mat[5] = y;
	scale_matrix.mat[10] = z;

	return scale_matrix;
}

void transform::scale(GLfloat x, GLfloat y, GLfloat z){
	scale_matrix = compute_scale(x, y, z);
}

vec3 transform::get_location()const {
	return vec3(translate_matrix.mat[12], translate_matrix.mat[13], translate_matrix.mat[14]);
}

vec3 transform::get_scale()const {
	return vec3(scale_matrix.mat[0], scale_matrix.mat[5], scale_matrix.mat[10]);
}

vec3 transform::get_forward_vector()const {
	return vec3(rotate_matrix.mat[2], rotate_matrix.mat[6], rotate_matrix.mat[10]);
}

mat4x4  transform::get_rotator()const {
	return rotate_matrix;
}

mat4x4 transform::get_transform()const {
	return  full_transform;
}

void transform::update_transform() {
	full_transform = scale_matrix * rotate_matrix * translate_matrix;
}