#pragma once

#include "GL/glew.h"
#include "transform.h"

class component
{
	public:
		component() {
		};
		~component() {
		};
	public:
		virtual void init_component();
		virtual void input();
		virtual void update();
		virtual void render();

		void set_transform(transform* obj_transfrom) {
			entity_transform = obj_transfrom;
		}

	public:
		transform* entity_transform;
};

