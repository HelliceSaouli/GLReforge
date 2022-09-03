#include "material.h"

#include "simpleshader.h"
material::material() {

	/*set up the albedo texture to default texture*/
	albedomap = new texture(GL_TEXTURE_2D, "defaults/default_uv_texture.jpg");
	albedomap->load_texture();
	is_default_loaded = GL_TRUE;
}

material::~material() {
	//TODO need some texture cleaning
}

void material::set_albedo_texture(const std::string& image_name) {
	if (is_default_loaded) {
		delete albedomap;
		is_default_loaded = GL_FALSE;
	}
	albedomap = new texture(GL_TEXTURE_2D, image_name);
	albedomap->load_texture();
	
}

void material::material_use_albedo_texture() {
		albedomap->use_texture(GL_TEXTURE0);
}

void material::init_shader() {
	material_shader = &simpleshader::get_instance();
}

void material::bind_material_shader() {
	material_shader->bind_shader();
}


void material::update_material_uniform_shader(camera* cam, const mat4x4& obj_transform,
	std::vector<lightsource*> light) {
	material_shader->uniforms_update(cam, obj_transform, light);
}