#include "simpleshader.h"

#include "resouceloader.h"

/* explicitly calling the base class constractor for safety reasons */
simpleshader::simpleshader() :shader{} {

	std::string vertex_src = resouceloader::load_shader_source("basicprogram.vert");
	std::string fragement_src = resouceloader::load_shader_source("basicprogram.frag");
	add_vertex_shader(vertex_src);
	add_fragement_shader(fragement_src);
	compile_program();
	
	/* manage uniforms */
	add_uniform("transfrom_matrix");
	add_uniform("projection_matrix");
	add_uniform("camera_matrix");
}


void simpleshader::uniforms_update(const mat4x4& cam_projection, const mat4x4& cam_transform,
	const mat4x4& obj_transform, material* obj_material) {
	uniformMatrix4("transfrom_matrix", obj_transform);
	uniformMatrix4("projection_matrix", cam_projection);
	uniformMatrix4("camera_matrix", cam_transform);

	obj_material->material_use_albedo_texture();
}