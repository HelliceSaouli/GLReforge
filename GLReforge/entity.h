#pragma once

#include <vector>

#include "GL/glew.h"

#include "component.h"
#include "transform.h"

class entity
{
	public:
		entity(GLboolean _is_root = GL_FALSE);
		~entity();
	
	public:
		GLboolean has_children()const;

		void input();
		void update();
		void render();

		void add_entity_child(entity* child);
		void add_entity_componenet(component* object_component);
		void set_transform(transform* entt_transform) {
			entity_transfrom = entt_transform;
		}
	private:
		GLboolean is_root;
		std::vector<entity*> childrens;
		std::vector<component*> entity_components;

		transform* entity_transfrom;
};

