#pragma once

#include "GL/glew.h"

#include <vector>
#include "vertex.h"


class mesh
{
	public:
		mesh();
		~mesh();
	
	public:
		void create_geometry_buffer();
		void glmemcpy(const std::vector<vertex>& vertrices);
		void mesh_draw();
	private:
		GLuint vertex_buffer_object;
		GLuint vertex_array_object;
		GLuint buffer_size;
		
};

