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

vertex::vertex(const vec3& position, const vec3& uv, const vec3& normal) {
	vertex_position = position;
	vertex_texture_uv = uv;
	vertex_normal = normal;
	vertex_tangent = vec3(0.0f, 0.0f, 0.0f);
}

vertex::vertex(const vec3& position, const vec3& uv, const vec3& normal, const vec3& tangent) {
	vertex_position = position;
	vertex_texture_uv = uv;
	vertex_normal = normal;
	vertex_tangent = tangent;
}

vertex::vertex(const vec3& position, const vec3& uv, const vec3& normal, const vec3& tangent, const vec3& bitangent) {
	vertex_position = position;
	vertex_texture_uv = uv;
	vertex_normal = normal;
	vertex_tangent = tangent;
	vertex_bitangent = bitangent;
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

void vertex::set_vertex_normal(const vec3& normal) {
	 vertex_normal = normal;
}

vec3 vertex::get_vertex_normal()const {
	return vertex_normal;
}

void vertex::set_vertex_tangent_coordinate(const vec3& t) {
	vertex_tangent = t;
}


vec3 vertex::get_vertex_tangent()const {
	return vertex_tangent;
}

void vertex::set_vertex_bitangent_coordinate(const vec3& b) {
	vertex_tangent = b;
}

vec3 vertex::get_vertex_bitangent()const {
	return vertex_bitangent;
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
		//normal
		vb[i * vertex_size + 5] = buffer[i].get_vertex_normal().x;
		vb[i * vertex_size + 6] = buffer[i].get_vertex_normal().y;
		vb[i * vertex_size + 7] = buffer[i].get_vertex_normal().z;
		//tangent
		vb[i * vertex_size + 8] = buffer[i].get_vertex_tangent().x;
		vb[i * vertex_size + 9] = buffer[i].get_vertex_tangent().y;
		vb[i * vertex_size + 10] = buffer[i].get_vertex_tangent().z;
		//bitangent
		vb[i * vertex_size + 11] = buffer[i].get_vertex_bitangent().x;
		vb[i * vertex_size + 12] = buffer[i].get_vertex_bitangent().y;
		vb[i * vertex_size + 13] = buffer[i].get_vertex_bitangent().z;
	}
	return vb;
}