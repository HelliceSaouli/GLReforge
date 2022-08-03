#include "camera.h"
#include "defines.h"
camera::camera() {

}

camera::~camera() {

}

void camera::set_camera_projection(GLfloat fov, GLfloat aratio, GLfloat near, GLfloat far) {
	projection = mat4x4(0.0f);

	fov = fov * (GLfloat)TORADIEN * 0.5;
	GLfloat f = tan(fov);
	GLfloat range = near - far;
	projection.mat[0] = 1.0f / f;
	projection.mat[5] = 1.0f / (f * aratio);
	projection.mat[10] = (-near - far) / range;
	projection.mat[14] = 2.0f * near * far / range;
	projection.mat[11] = 1.0f;
}