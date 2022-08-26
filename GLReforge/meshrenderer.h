#pragma once
#include "component.h"

#include "staticmodel.h"

#include "lightsource.h"
#include "pointlight.h"

#include "camera.h"
#include "shader.h"

#include <vector>

class meshrenderer :public component
{
	public:
		meshrenderer(staticmodel* _model, std::vector<lightsource*> _lights, camera* _cam);
		~meshrenderer();
	
	public:
		void render(shader* shader_model) override;

	private:
		staticmodel* model;
		std::vector<lightsource*> lights;
		camera* cam;
};

