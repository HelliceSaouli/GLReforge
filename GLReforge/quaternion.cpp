#include "quaternion.h"

quaternion::quaternion(GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _w) {
	x = _x;
	y = _y;
	z = _z;
	w = _w;

}

quaternion::quaternion() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}

quaternion::~quaternion() {

}


void quaternion::normalize() {
	GLfloat magnitud = length();
	x /= magnitud;
	y /= magnitud;
	z /= magnitud;
	w /= magnitud;
}

GLfloat quaternion::length() {
	return sqrt(x * x + y * y + z * z + w * w);
}

quaternion quaternion::conjugate()const {
	return quaternion(-x, -y, -z, w);
}

quaternion quaternion::operator *(const quaternion& b)const {
	GLfloat _w = w * b.w - x * b.x - y * b.y - z * b.z;
	GLfloat _x = x * b.w + w * b.x + y * b.z - z * b.y;
	GLfloat _y = y * b.w + w * b.y + z * b.x - x * b.z;
	GLfloat _z = z * b.w + w * b.z + x * b.y - y * b.x;

	return quaternion(_x, _y, _z, _w);
}

quaternion quaternion::operator *(const vec3& b)const {
	GLfloat _w = -x * b.x - y * b.y - z * b.z;
	GLfloat _x = w * b.x + y * b.z - z * b.y;
	GLfloat _y = w * b.y + z * b.x - x * b.z;
	GLfloat _z = w * b.z + x * b.y - y * b.x;

	return quaternion(_x, _y, _z, _w);
}