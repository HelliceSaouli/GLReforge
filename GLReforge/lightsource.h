#pragma once

#include "GL/glew.h"

#include "transform.h"

/* The implementation will be a static light */
class lightsource
{
	public:
		lightsource();
		~lightsource();

	public:
		vec3 get_position()const;
		vec3 get_direction()const;
		vec3 get_color()const;

		void set_position(GLfloat x, GLfloat y, GLfloat z);
		void set_direction(GLfloat xangle, GLfloat yangle, GLfloat zangle);
		void set_color(GLfloat x, GLfloat y, GLfloat z);

		virtual void update() = 0; /* TODO for now this function is just here */
	private:
		transform source_transform;
		vec3 light_color;
};

