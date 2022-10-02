#pragma once
#include "GL/glew.h"

#include "vec3.h"
#include "texture.h"

#include "lightsource.h"
#include "sunlight.h"
#include "pointlight.h"

#include <vector>

class shadowmap
{
	public:
		shadowmap(std::vector<lightsource*>  _lights);
		~shadowmap();


	private:
		std::vector<lightsource*>  lights; /* I don't think i need this will see later */
		std::vector<texture*> depthtextures;
};

