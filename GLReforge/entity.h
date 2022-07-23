#pragma once

#include <vector>

#include "GL/glew.h"

class entity
{
	public:
		entity(GLboolean _is_root = GL_FALSE);
		~entity();
	
	public:
		GLboolean has_children()const;
	private:
		GLboolean is_root;
		std::vector<entity> childrens;
};

