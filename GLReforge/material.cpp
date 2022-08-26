#include "material.h"

material::material() {

	/*set up the albedo texture to default texture*/
	albedo = new texture(GL_TEXTURE_2D, "defaults/default_uv_texture.jpg");
	albedo->load_texture();
	is_default_loaded = GL_TRUE;
}

material::~material() {
	//TODO need some texture cleaning
}

void material::set_albedo_texture(const std::string& image_name) {
	if (is_default_loaded) {
		delete albedo;
		is_default_loaded = GL_FALSE;
	}
	albedo = new texture(GL_TEXTURE_2D, image_name);
	albedo->load_texture();
}

void material::material_use_albedo_texture() {
		albedo->use_texture(GL_TEXTURE0);
}