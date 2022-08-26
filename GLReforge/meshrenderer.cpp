#include "meshrenderer.h"

#include "simpleshader.h"

meshrenderer::meshrenderer(staticmodel* _model, std::vector<lightsource*> _lights, camera* _cam) {

	model = _model;
	lights = _lights;
	cam = _cam;

	if (model == NULL || cam == NULL) {
		std::cout << "something  wrong" << std::endl;
		exit(0);
	}
}

meshrenderer::~meshrenderer() {

}

void meshrenderer::render(shader* shader_model) {
	for (GLuint index = 0; index < model->number_of_meshes; index++) {
		shader_model->bind_shader();
		shader_model->uniforms_update(cam, entity_transform->get_transform(), lights);
		model->use_material_albedo(index);
		model->draw_model_part(index);
	}
}