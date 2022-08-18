#pragma once
#include "GL/glew.h"

#include "lightsource.h"
#include "vec3.h"

class pointlight : public lightsource
{
	public:
		pointlight(GLfloat c, GLfloat l, GLfloat q, GLfloat r);
		~pointlight();

		void update() override;
	public:
		GLfloat constant;
		GLfloat linear;
		GLfloat quadratic;
		GLfloat max_range;
		
};

