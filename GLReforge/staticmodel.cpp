#include "staticmodel.h"

#include <iostream>
staticmodel::staticmodel() {
	
}

staticmodel::~staticmodel() {

}

void staticmodel::init_model(GLuint nbr_of_meshs, GLuint nbr_of_matrs) {
	number_of_meshes = nbr_of_meshs;
	number_of_materials = nbr_of_matrs;

	model_parts.resize(number_of_meshes);
	material_parts.resize(number_of_materials);

	for (GLuint idx = 0; idx < number_of_meshes; idx++) {
		model_parts[idx] = new mesh();
	}

	for (GLuint idx = 0; idx < number_of_materials; idx++) {
		material_parts[idx] = new material();
	}

}

void staticmodel::add_mesh(GLuint matindx, const std::vector<vertex>& buffer, 
										   const std::vector<GLuint>& indices, GLuint indx) {
	model_parts[indx]->material_index = matindx;
	model_parts[indx]->create_geometry_buffer(buffer, indices);
}

void staticmodel::set_albedo_texture(std::string fullpath, GLuint indx) {
	material_parts[indx]->set_albedo_texture(fullpath);
}

void staticmodel::use_material_albedo(GLuint indx) {
	if (model_parts[indx]->material_index < material_parts.size()) {
		material_parts[model_parts[indx]->material_index]->material_use_albedo_texture();
	}	
}

void staticmodel::set_normal_texture(std::string fullpath, GLuint indx) {
	material_parts[indx]->set_normal_texture(fullpath);
}

void staticmodel::use_material_normal(GLuint indx) {
	if (model_parts[indx]->material_index < material_parts.size()) {
		material_parts[model_parts[indx]->material_index]->material_use_normal_texture();
	}
}

void staticmodel::draw_model_part(GLuint indx) {
	model_parts[indx]->mesh_draw();
}

void staticmodel::init_material_shader() {
	for (GLuint idx = 0; idx < number_of_materials; idx++) {
		material_parts[idx]->init_shader();
	}
}

void staticmodel::bind_material_shader(GLuint indx) {
	material_parts[model_parts[indx]->material_index]->bind_material_shader();
}

void staticmodel::update_material_uniform_shader(GLuint indx, camera* cam, const mat4x4& obj_transform,
	std::vector<lightsource*> lights) {
	material_parts[model_parts[indx]->material_index]->update_material_uniform_shader(cam, obj_transform, lights);
}