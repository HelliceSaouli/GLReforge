#include <stdexcept>

#include "vec3.h"
#include "quaternion.h"

vec3::vec3() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

vec3::vec3(GLfloat _x, GLfloat _y, GLfloat _z) {
	x = _x;
	y = _y;
	z = _z;
}

vec3::~vec3() {

}

vec3 vec3::operator *(const GLfloat v)const {
	return vec3(x * v, y * v, z * v);
}

vec3 vec3::operator /(const GLfloat v)const {
	if (v != 0.0f) {
		return vec3(x / v, y / v, z / v);
	}

	return vec3(0.0f, 0.0f, 0.0f);
}
		
vec3 vec3::operator +(const GLfloat v)const {
	return vec3(x * v, y * v, z * v);
}

vec3 vec3::operator -(const GLfloat v)const {
	return vec3(x * v, y * v, z * v);
}

vec3 vec3::operator *(const vec3& v)const {
	return vec3(x * v.x, y * v.y, z * v.z);
}

vec3 vec3::operator +(const vec3& v)const {
	return vec3(x + v.x, y + v.y, z + v.z);
}

vec3 vec3::operator -(const vec3& v)const {
	return vec3(x - v.x, y - v.y, z - v.z);
}

void vec3::negative() {
	x = -x;
	y = -y;
	z = -z;
}

void vec3::normalize() {
	GLfloat magnitud = length();
	x /= magnitud;
	y /= magnitud;
	z /= magnitud;
}


GLfloat vec3::length() {
	return sqrt(x * x + y * y + z * z);
}

GLfloat vec3::length_square() {
	return (x * x + y * y + z * z);
}

GLfloat vec3::dot_product(const vec3& b)const {
	return (x * b.x + y * b.y + z * b.z);
}

vec3 vec3::cross(const vec3& v)const {
	vec3 c(0.0f, 0.0f, 0.0f);

	c.x = y * v.z - z * v.y;
	c.y = z * v.x - x * v.z;
	c.z = x * v.y - y * v.x;

	return c;
}

vec3 vec3::normalized() {
	GLfloat magnitud = length();
	return vec3(x / magnitud, y / magnitud, z / magnitud);
}

vec3 vec3::rotate(GLfloat angleinradiant, const vec3& axis)const {
	// TODO: need to implement quaternion---> done
	GLfloat sinhalfangle = (GLfloat)sin(angleinradiant / 2.0f);
	GLfloat coshalfangle = (GLfloat)cos(angleinradiant / 2.0f);

	quaternion rotation = quaternion(axis.x * sinhalfangle,  axis.y * sinhalfangle, axis.z * sinhalfangle, coshalfangle);
	quaternion conj = rotation.conjugate();

	quaternion rotator = (rotation * vec3(x, y, z)) * conj;

	return vec3(rotator.x, rotator.y, rotator.z);
}