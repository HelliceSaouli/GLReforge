#include "mesh.h"

mesh::mesh() {
	vertex_buffer_object = 0;
	vertex_array_object = 0;
	buffer_size = 0;
}

mesh::~mesh() {

}

void mesh::create_geometry_buffer() {
	
	/* VAO */
	glGenVertexArrays(1, &vertex_array_object);
	/* VBO */
	glGenBuffers(1, &vertex_buffer_object);
}

void mesh::glmemcpy(const std::vector<vertex>& vertrices) {

	
	buffer_size = (GLuint)vertrices.size() * vertex::vertex_size;
	GLfloat* buffer = vertex::vertecies_to_float(vertrices, buffer_size);

	glBindVertexArray(vertex_buffer_object);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);

	/* copying data and telling opengl how to interpret it */
	glBufferData(GL_ARRAY_BUFFER, buffer_size * sizeof(GLfloat), buffer, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex::vertex_size * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	/* unbind the vao*/
	glBindVertexArray(0);
}


void mesh::mesh_draw() {
	glBindVertexArray(vertex_array_object);
	glDrawArrays(GL_TRIANGLES, 0, buffer_size / vertex::vertex_size);
	glBindVertexArray(0);
}