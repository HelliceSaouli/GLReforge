#include "camera.h"
#include "defines.h"
camera::camera() {
	camera_position = vec3(0.0f, 0.0f, 0.0f);
    camera_up       = vec3(0.0f, 1.0f, 0.0f);
	camera_forward  = vec3(0.0f, 0.0f, 1.0f);
	camera_transform = mat4x4::identity();
}

camera::~camera() {

}
void camera::set_camera_position(GLfloat x, GLfloat y, GLfloat z) {
	camera_position = vec3(x, y, z);
}

void camera::camera_look_at(const vec3& target) {
	camera_forward = target - camera_position;
	camera_forward.normalize();

	camera_update_transform();

}

void camera::move_camera(vec3 direction, GLfloat distance) {
	camera_position = camera_position + direction * distance;
}

vec3 camera::get_camera_left() {
	vec3 left = camera_forward.cross(camera_up);
	left.normalize();
	return left;
}

vec3 camera::get_camera_right() {
	vec3 right = camera_up.cross(camera_forward);
	right.normalize();
	return right;
}
//TODO fix the bug gumble look at 180
void camera::camera_add_input_pitch(GLfloat senstive, GLfloat amount) {
	GLfloat pitch = senstive * amount * TORADIEN;
	vec3    yaxis = vec3(0.0f, 1.0f, 0.0f);

	vec3    haxis  = yaxis.cross(camera_forward);
	haxis.normalize();
	camera_forward = camera_forward.rotate(pitch, haxis);
	camera_forward.normalize();
	camera_up = camera_forward.cross(haxis);
	camera_up.normalize();
}


void camera::camera_add_input_yaw(GLfloat senstive, GLfloat amount) {
	GLfloat yaw = senstive * amount * TORADIEN;
	vec3    yaxis = vec3(0.0f, 1.0f, 0.0f);

	vec3    haxis = yaxis.cross(camera_forward);
	haxis.normalize();
	camera_forward = camera_forward.rotate(yaw, yaxis);
	camera_forward.normalize();
	camera_up = camera_forward.cross(haxis);
	camera_up.normalize();
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

void camera::camera_update_transform() {
	vec3 right = get_camera_right();
	camera_transform.mat[0] = right.x;
	camera_transform.mat[1] = right.y;
	camera_transform.mat[2] = right.z;
	camera_transform.mat[3] = 0.0f;

	camera_transform.mat[4] = camera_up.x;
	camera_transform.mat[5] = camera_up.y;
	camera_transform.mat[6] = camera_up.z;
	camera_transform.mat[7] = 0.0f;

	camera_transform.mat[8] = camera_forward.x;
	camera_transform.mat[9] = camera_forward.y;
	camera_transform.mat[10] = camera_forward.z;
	camera_transform.mat[11] = 0.0f;


	camera_transform.mat[12] = -right.dot_product(camera_position);
	camera_transform.mat[13] = -camera_up.dot_product(camera_position);
	camera_transform.mat[14] = -camera_forward.dot_product(camera_position);
	camera_transform.mat[15] = 1.0;
}