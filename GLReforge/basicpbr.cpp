#include "basicpbr.h"

#include "resouceloader.h"

#include "sunlight.h"

basicpbr::basicpbr() :shader{} {

	
	std::string vertex_src = resouceloader::load_shader_source("basicprogram.vert");
	std::string fragement_src = resouceloader::load_shader_source("basicprogram.frag");
	add_vertex_shader(vertex_src);
	add_fragement_shader(fragement_src);
	compile_program();

	/* manage uniforms */
	add_uniform("transfrom_matrix");
	add_uniform("projection_matrix");
	add_uniform("camera_matrix");
	add_uniform("camera_world_location");
	/* simple point lighting with one source */
	
	add_uniform("sunlightcolor");
	add_uniform("sunlightdirection");
}

void basicpbr::uniforms_update(camera* cam, const mat4x4& obj_transform,
	std::vector<lightsource*> lights) {

}