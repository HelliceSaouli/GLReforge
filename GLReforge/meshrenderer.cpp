#include "meshrenderer.h"

#include "simpleshader.h"

meshrenderer::meshrenderer(mesh* _entity_mesh, material* _mesh_material,
						   std::vector<lightsource*> _lights, camera* _cam) {

	entity_mesh = _entity_mesh;
	mesh_material = _mesh_material;
	lights = _lights;
	cam = _cam;

	if (entity_mesh == NULL || mesh_material == NULL || cam == NULL) {
		std::cout << "something  wrong" << std::endl;
		exit(0);
	}
	/* init the singlton */
	simpleshader& asimpleshader = simpleshader::get_instance();
}

meshrenderer::~meshrenderer() {

}

void meshrenderer::render() {
	simpleshader& asimpleshader = simpleshader::get_instance();
	asimpleshader.bind_shader();
	asimpleshader.uniforms_update(cam, entity_transform->get_transform(), mesh_material, lights);
	entity_mesh->mesh_draw();
}