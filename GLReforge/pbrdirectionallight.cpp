#include "pbrdirectionallight.h"

#include "resouceloader.h"
#include "sunlight.h"


/* explicitly calling the base class constractor for safety reasons */
pbrdirectionallight::pbrdirectionallight() :shader{} {
	std::string vertex_src = resouceloader::load_shader_source("simplebpr.vert");
	std::string fragement_src = resouceloader::load_shader_source("simplebpr.frag");
	add_vertex_shader(vertex_src);
	add_fragement_shader(fragement_src);
	compile_program();

	/* manage uniforms */
	add_uniform("transfrom_matrix");
	add_uniform("projection_matrix");
	add_uniform("camera_matrix");
	add_uniform("camera_world_location");

	/* simple point lighting with one source */
	add_uniform("lightcolor");
	add_uniform("intensity");
	add_uniform("sun_direction");
}


void pbrdirectionallight::uniforms_update(camera* cam, const mat4x4& obj_transform,
	std::vector<lightsource*> lights) {
	/* simple shader only with one light source */
	uniformMatrix4("transfrom_matrix", obj_transform);
	uniformMatrix4("projection_matrix", cam->get_projection());
	uniformMatrix4("camera_matrix", cam->get_transform());
	uniform3f("camera_world_location", cam->get_camera_current_location());

	sunlight* sun_light = dynamic_cast<sunlight*>(lights[0]);
	uniform3f("lightcolor", sun_light->get_color());
	uniform1f("intensity", sun_light->intensity);
	uniform3f("sun_direction", sun_light->get_direction());
}
