#include "lightsource.h"

lightsource::lightsource() {
	/* white color initialization */
	light_color = vec3(1.0f, 1.0f, 1.0f);

	shadowmap_width = 256;
	shadowmap_hight = 256;

	cast_shadow = GL_TRUE;
}

lightsource::~lightsource() {

}

GLuint lightsource::get_shadowmap_width()const {
	return shadowmap_width;
}
GLuint lightsource::get_shadowmap_hight()const {
	return shadowmap_hight;
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

GLboolean lightsource::is_source_cast_shadow()const {
	return cast_shadow;
}

void lightsource::set_cast_shadow(GLboolean val) {
	cast_shadow = val;
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

void lightsource::set_shadowmap_width(GLuint val) {
	shadowmap_width = val;
}

void lightsource::set_shadowmap_hight(GLuint val) {
	shadowmap_hight = val;
}