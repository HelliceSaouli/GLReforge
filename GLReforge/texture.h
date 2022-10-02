#pragma once

#include "GL/glew.h"


#include <string>

class texture
{
	public:
		texture(GLenum target, const std::string& _image_name);

		texture() {
			/* general constractor */
			/* helpfull to create depth maps or other maps*/
		}; 
		~texture();


	public:
		GLboolean load_srgb_texture();
		GLboolean load_non_srgb_maps();

		void use_texture(GLenum texture_unit);
	private:
		GLuint texture_object;
		GLenum texture_target;
		std::string image_name;
};

