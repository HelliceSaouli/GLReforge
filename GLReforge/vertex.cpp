#include "vertex.h"

vertex::vertex() {
}
vertex::vertex(GLfloat x, GLfloat y, GLfloat z) {
	vertex_position.x = x;
	vertex_position.y = y;
	vertex_position.z = z;
}

vertex::vertex(const vec3& position, const vec3& uv) {
	vertex_position   = position;
	vertex_texture_uv = uv;
}

vertex::~vertex() {

}

void vertex::set_vertex_position(const vec3& position) {
	vertex_position = position;
}

vec3 vertex::get_vertex_poisition()const {
	return vertex_position;
}

void vertex::set_vertex_uv_coordinate(const vec3& uv) {
	vertex_texture_uv = uv;
}

vec3 vertex::get_vertex_uv()const {
	return vertex_texture_uv;
}

GLfloat* vertex::vertecies_to_float(const std::vector<vertex>& buffer, GLuint buffer_size) {

	GLfloat* vb = new GLfloat[buffer_size];

	for (GLuint i = 0; i < (GLuint)buffer.size(); i++) {
		//pos
		vb[i * vertex_size] = buffer[i].get_vertex_poisition().x;
		vb[i * vertex_size + 1] = buffer[i].get_vertex_poisition().y;
		vb[i * vertex_size + 2] = buffer[i].get_vertex_poisition().z;
		// UV
		vb[i * vertex_size + 3] = buffer[i].get_vertex_uv().x;
		vb[i * vertex_size + 4] = buffer[i].get_vertex_uv().y;
	}
	return vb;
}