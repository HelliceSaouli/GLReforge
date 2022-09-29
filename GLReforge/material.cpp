#include "material.h"

// #include "simpleshader.h"
#include "pbrdirectionallight.h"

material::material() {
	/*set up the albedo texture to default texture*/
	albedomap = new texture(GL_TEXTURE_2D, "defaults/default_uv_texture.jpg");
	albedomap->load_srgb_texture();
	is_default_loaded = GL_TRUE;

	/* pbr single values */
	albedo  = vec3(1.0f, 1.0f, 1.0f);
	metalic   = 0.0f;
	roughness = 0.5f;
	ambeintocclusion = 1.0f;

	/*when creating material you need to set this according to what you need*/
	
	use_albedo_map    = 0;
	use_metalic_map   = 0;
	use_roughness_map = 0;
	use_ao_map        = 0;
	use_normal_map    = 0;
}

material::~material() {
	//TODO need some texture cleaning
}

void material::set_albedo_texture(const std::string& image_name) {
	if (is_default_loaded) {
		delete albedomap;
		is_default_loaded = GL_FALSE;
	}
	use_albedo_map = 1;
	albedomap = new texture(GL_TEXTURE_2D, image_name);
	albedomap->load_srgb_texture();
	
}

void material::material_use_albedo_texture() {
	albedomap->use_texture(GL_TEXTURE0);
}

void material::set_metalic_texture(const std::string& image_name) {
	use_metalic_map = 1;
	metalicmap = new texture(GL_TEXTURE_2D, image_name);
	metalicmap->load_non_srgb_maps();
}

void material::material_use_metalic_texture() {
	if (use_metalic_map == 1 && metalicmap != NULL) {
		metalicmap->use_texture(GL_TEXTURE1);
	}
	
}

void material::set_roughness_texture(const std::string& image_name) {
	use_roughness_map = 1;
	roughnessmap = new texture(GL_TEXTURE_2D, image_name);
	roughnessmap->load_non_srgb_maps();
}

void material::material_use_roughness_texture() {
	if (use_roughness_map == 1 && roughnessmap != NULL) {
		roughnessmap->use_texture(GL_TEXTURE2);
	}
	
}

void material::set_ao_texture(const std::string& image_name) {
	use_ao_map = 1;
	ambeintocclusionmap = new texture(GL_TEXTURE_2D, image_name);
	ambeintocclusionmap->load_non_srgb_maps();
}

void material::material_use_ao_texture() {
	if (use_ao_map == 1 && ambeintocclusionmap != NULL) {
		ambeintocclusionmap->use_texture(GL_TEXTURE3);
	}	
}

void material::set_normal_texture(const std::string& image_name) {
	use_normal_map = 1;
	normalmap = new texture(GL_TEXTURE_2D, image_name);
	normalmap->load_non_srgb_maps();
}

void material::material_use_normal_texture() {
	if (use_normal_map == 1 && normalmap != NULL) {
		normalmap->use_texture(GL_TEXTURE4);
	}	
}

void material::init_shader() {
	// material_shader = &simpleshader::get_instance();
	material_shader = &pbrdirectionallight::get_instance();

	if (material_shader == NULL) {
		std::cout << "material shader is null" << std::endl;
		exit(0);
	}
	//TODO add control uniform here ?
	material_shader->add_uniform("use_albedo_map");
	material_shader->add_uniform("use_metalic_map");
	material_shader->add_uniform("use_roughness_map");
	material_shader->add_uniform("use_ao_map");
	material_shader->add_uniform("use_normal_map");

	/* if the maps are not availble we use this instead */
	material_shader->add_uniform("albedo");
	material_shader->add_uniform("metalic");
	material_shader->add_uniform("roughness");
	material_shader->add_uniform("ambeintocclusion");
}

void material::bind_material_shader() {
	material_shader->bind_shader();
}


void material::update_material_uniform_shader(camera* cam, const mat4x4& obj_transform,
	std::vector<lightsource*> light) {
	material_shader->uniform1i("use_albedo_map", use_albedo_map);
	material_shader->uniform1i("use_metalic_map", use_metalic_map);
	material_shader->uniform1i("use_roughness_map", use_roughness_map);
	material_shader->uniform1i("use_ao_map", use_ao_map);
	material_shader->uniform1i("use_normal_map", use_normal_map);

	/* this shoud be updated if they exist .?*/
	material_shader->uniform3f("albedo", albedo);
	material_shader->uniform1f("metalic", metalic);
	material_shader->uniform1f("roughness", roughness);
	material_shader->uniform1f("ambeintocclusion", ambeintocclusion);

	material_shader->uniforms_update(cam, obj_transform, light);
}

