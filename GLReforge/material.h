#pragma once
#include "GL/glew.h"

#include "vec3.h"
#include "texture.h"

#include <vector>
#include <string>

class material
{
	public:
		material();
		~material();

	public:
		void set_albedo_texture(const std::string& image_name);
		void material_use_albedo_texture();
	private:
		/* TODO : implement a cleaning up function where you free texture from GPU memory */
		std::vector<texture*> albedo;
		GLboolean is_default_loaded;
};

