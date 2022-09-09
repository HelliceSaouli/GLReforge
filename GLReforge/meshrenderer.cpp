#include "meshrenderer.h"

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

void meshrenderer::init_component(){
	model->init_material_shader();
}

void meshrenderer::render() {
	/* TODO: shader should be part of material */
	for (GLuint index = 0; index < model->number_of_meshes; index++) {
		model->bind_material_shader(index);
		model->update_material_uniform_shader(index, cam, entity_transform->get_transform(), lights);
		model->use_material_albedo(index);
		model->use_material_normal(index);
		model->draw_model_part(index);
	}
}