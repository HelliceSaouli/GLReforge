#pragma once
#include "GL/glew.h"

#include "vec3.h"
#include "texture.h"

#include <vector>

class shadowmap
{
	public:
		shadowmap();
		~shadowmap();

		void add_shadow_map(GLuint w, GLuint h);
	private:
		std::vector<texture*> depthtextures;
};

