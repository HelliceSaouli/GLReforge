#pragma once
#include "component.h"

#include "staticmodel.h"

#include "lightsource.h"

#include "shadowmap.h"

#include "shader.h"

#include <vector>

class shadowmapcomp : public component
{

	public: 
		shadowmapcomp(shadowmap* _shadows, staticmodel* _model, std::vector<lightsource*> _lights);
		~shadowmapcomp();

		void render() override;
		void init_component() override;

	private:
		staticmodel* model;
		std::vector<lightsource*> lights;
		shadowmap* shadows;

		GLuint shadowmap_framebuffer;
};

