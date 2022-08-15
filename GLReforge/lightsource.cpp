#include "lightsource.h"

lightsource::lightsource() {
	/* white color initialization */
	light_color = vec3(1.0f, 1.0f, 1.0f);
}

lightsource::~lightsource() {

}

vec3 lightsource::get_position()const {
	return source_transform.get_location();
}

vec3 lightsource::get_direction()const {
	return source_transform.get_forward_vector();
}

vec3 lightsource::get_color()const {
	return light_color;
}

void lightsource::set_position(GLfloat x, GLfloat y, GLfloat z) {
	source_transform.translate(x, y, z);
}

void lightsource::set_direction(GLfloat xangle, GLfloat yangle, GLfloat zangle) {
	source_transform.rotation(xangle, yangle, zangle);
}

void lightsource::set_color(GLfloat x, GLfloat y, GLfloat z) {
	light_color = vec3(x, y, z);
}