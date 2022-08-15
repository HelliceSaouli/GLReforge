#include "simpleshader.h"

#include "resouceloader.h"

/* explicitly calling the base class constractor for safety reasons */
simpleshader::simpleshader() :shader{} {

	ambient_light = vec3(0.8f, 0.8f, 0.8f);
	std::string vertex_src = resouceloader::load_shader_source("basicprogram.vert");
	std::string fragement_src = resouceloader::load_shader_source("basicprogram.frag");
	add_vertex_shader(vertex_src);
	add_fragement_shader(fragement_src);
	compile_program();
	
	/* manage uniforms */
	add_uniform("transfrom_matrix");
	add_uniform("projection_matrix");
	add_uniform("camera_matrix");
	add_uniform("ambient");
}


void simpleshader::uniforms_update(const mat4x4& cam_projection, const mat4x4& cam_transform,
	const mat4x4& obj_transform, material* obj_material) {
	uniformMatrix4("transfrom_matrix", obj_transform);
	uniformMatrix4("projection_matrix", cam_projection);
	uniformMatrix4("camera_matrix", cam_transform);
	uniform3f("ambient", ambient_light);
	obj_material->material_use_albedo_texture();
}

void simpleshader::set_ambient_light(GLfloat x, GLfloat y, GLfloat z) {
	ambient_light = vec3(x, y, z);
}