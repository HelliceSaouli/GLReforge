#pragma once

#include "GL/glew.h"

#include "vec3.h"

#include <vector>

class vertex
{
	public:
		vertex();
		vertex(GLfloat x, GLfloat y, GLfloat z); // this to be removed
		vertex(const vec3& position, const vec3& uv);
		vertex(const vec3& position, const vec3& uv, const vec3& normal);
		~vertex();
	
	public:
		void set_vertex_position(const vec3& position);
		void set_vertex_uv_coordinate(const vec3& uv);
		void set_vertex_normal(const vec3& normal);

		/*TODO: I will make function that return directly to vertex buffer (array of floats) */
		vec3 get_vertex_poisition()const;
		vec3 get_vertex_uv()const;
		vec3 get_vertex_normal()const;
		/* utiliy function */
		static GLfloat* vertecies_to_float(const std::vector<vertex>& buffer, GLuint buffer_size);
	private:
		vec3 vertex_position;
		vec3 vertex_texture_uv;
		vec3 vertex_normal;
	public:
		static const GLuint vertex_size{ 8 };
};

