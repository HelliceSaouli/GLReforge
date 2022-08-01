#include "vertex.h"

vertex::vertex() {
}
vertex::vertex(GLfloat x, GLfloat y, GLfloat z) {
	vertex_position.x = x;
	vertex_position.y = y;
	vertex_position.z = z;
}

vertex::~vertex() {

}

void vertex::set_vertex_position(const vec3& position) {
	vertex_position = position;
}

vec3 vertex::get_vertex_poisition()const {
	return vertex_position;
}

GLfloat* vertex::vertecies_to_float(const std::vector<vertex>& buffer, GLuint buffer_size) {

	GLfloat* vb = new GLfloat[buffer_size];

	for (GLuint i = 0; i < (GLuint)buffer.size(); i++) {
		vb[i * vertex_size] = buffer[i].get_vertex_poisition().x;
		vb[i * vertex_size + 1] = buffer[i].get_vertex_poisition().y;
		vb[i * vertex_size + 2] = buffer[i].get_vertex_poisition().z;
	}
	return vb;
}