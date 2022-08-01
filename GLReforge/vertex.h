#pragma once

#include "GL/glew.h"

#include "vec3.h"

#include <vector>

class vertex
{
	public:
		vertex();
		vertex(GLfloat x, GLfloat y, GLfloat z);
		~vertex();
	
	public:
		void set_vertex_position(const vec3& position);

		/*TODO: I will make function that return directly to vertex buffer (array of floats) */
		vec3 get_vertex_poisition()const;

		/* utiliy function */
		static GLfloat* vertecies_to_float(const std::vector<vertex>& buffer, GLuint buffer_size);
	private:
		vec3 vertex_position;

	public:
		static const GLuint vertex_size{ 3 };
};

