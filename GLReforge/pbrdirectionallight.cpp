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
	add_uniform("number_of_lights");

	/* simple point lighting with one source */
	for (GLuint i = 0; i < MAX_SUPPORTED_LIGHT; i++) {
		add_uniform("lightcolor[" + std::to_string(i) + "]");
		add_uniform("intensity["  + std::to_string(i) + "]");
		add_uniform("sun_direction[" + std::to_string(i) + "]");
	}

}


void pbrdirectionallight::uniforms_update(camera* cam, const mat4x4& obj_transform,
	std::vector<lightsource*> lights) {
	/* simple shader only with one light source */
	uniformMatrix4("transfrom_matrix", obj_transform);
	uniformMatrix4("projection_matrix", cam->get_projection());
	uniformMatrix4("camera_matrix", cam->get_transform());
	uniform3f("camera_world_location", cam->get_camera_current_location());
	uniform1i("number_of_lights", (GLint)lights.size());

	for (GLuint i = 0; i < lights.size(); i++) {
		if (i >= MAX_SUPPORTED_LIGHT)
			break;

		sunlight* sun_light = dynamic_cast<sunlight*>(lights[i]);
		uniform3f("lightcolor[" + std::to_string(i) + "]", sun_light->get_color());
		uniform1f("intensity[" + std::to_string(i) + "]", sun_light->intensity);
		uniform3f("sun_direction[" + std::to_string(i) + "]", sun_light->get_direction());
	}
}
