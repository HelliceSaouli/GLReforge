#pragma once
#include "GL/glew.h"

#include "lightsource.h"
#include "vec3.h"

class sunlight : public lightsource
{
	public:
		sunlight();
		~sunlight();
	public:
		void update() override;
};

