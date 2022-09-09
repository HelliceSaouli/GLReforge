#pragma once

#include "GL/glew.h"


#include <string>

class texture
{
	public:
		texture(GLenum target, const std::string& _image_name);
		~texture();


	public:
		GLboolean load_texture();
		GLboolean load_normal_maps();

		void use_texture(GLenum texture_unit);
	private:
		GLuint texture_object;
		GLenum texture_target;
		std::string image_name;
};

