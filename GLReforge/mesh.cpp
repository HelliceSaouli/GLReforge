#include "mesh.h"

mesh::mesh() {
	vertex_buffer_object = 0;
	vertex_array_object = 0;
	element_buffer_object = 0;
	buffer_size = 0;
	material_index = 0;
}

mesh::~mesh() {

}


void mesh::create_geometry_buffer(const std::vector<vertex>& vertrices, const std::vector<GLuint>& indices) {
	
	buffer_size = (GLuint)vertrices.size() * vertex::vertex_size;
	number_of_indices = (GLuint)indices.size();

	GLfloat* buffer = vertex::vertecies_to_float(vertrices, buffer_size);


	glGenVertexArrays(1, &vertex_array_object);
	glBindVertexArray(vertex_array_object);

	glGenBuffers(1, &vertex_buffer_object);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);

	

	/* copying data and telling opengl how to interpret it */
	glBufferData(GL_ARRAY_BUFFER, buffer_size * sizeof(GLfloat), buffer, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex::vertex_size * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0); /* position*/

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertex::vertex_size * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1); /* uv */

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, vertex::vertex_size * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2); /* normal*/

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, vertex::vertex_size * sizeof(GLfloat), (void*)(8 * sizeof(GLfloat)));
	glEnableVertexAttribArray(3); /* tangent*/

	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, vertex::vertex_size * sizeof(GLfloat), (void*)(11 * sizeof(GLfloat)));
	glEnableVertexAttribArray(4); /* bitangent*/

	glGenBuffers(1, &element_buffer_object);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, number_of_indices * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
	/* unbind the vao*/
	glBindVertexArray(0);
	
	/* clean cpu memory */
	delete buffer;
}


void mesh::mesh_draw() {
	glBindVertexArray(vertex_array_object);
	glDrawElements(GL_TRIANGLES, number_of_indices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}