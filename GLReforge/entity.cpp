#include "entity.h"


entity::entity(GLboolean _is_root) {
	is_root = _is_root;
	entity_transfrom = new transform();
}

entity::~entity() {
	//TODO
}

/* check if the this node has childrens*/
GLboolean entity::has_children()const {
	return (GLboolean)childrens.empty();
}


void entity::input() {

	for (auto comp : entity_components) {
		comp->input();
	}

	for (auto child : childrens) {
		child->input();
	}
}

void entity::update() {

	for (auto comp : entity_components) {
		comp->update();
	}

	for (auto child : childrens) {
		child->update();
	}
}

void entity::render() {
	
	for (auto comp : entity_components) {
		comp->render();
	}

	for (auto child : childrens) {
		child->render();
	}

}

void entity::add_entity_child(entity* child) {
	childrens.push_back(child);
}

void entity::add_entity_componenet(component* object_component) {
	entity_components.push_back(object_component);
	entity_components.back()->set_transform(entity_transfrom);
}

