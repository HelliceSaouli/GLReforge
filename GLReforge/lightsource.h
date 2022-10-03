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

		GLuint get_shadowmap_width()const;
		GLuint get_shadowmap_hight()const;

		GLboolean is_source_cast_shadow()const;

		void set_position(GLfloat x, GLfloat y, GLfloat z);
		void set_direction(GLfloat xangle, GLfloat yangle, GLfloat zangle);
		void set_color(GLfloat x, GLfloat y, GLfloat z);
		void set_cast_shadow(GLboolean val);
		void set_shadowmap_width(GLuint val);
		void set_shadowmap_hight(GLuint val);

		virtual void update() = 0; /* TODO for now this function is just here */
	private:
		transform source_transform;
		vec3 light_color;

		GLboolean cast_shadow;
		GLuint shadowmap_width;
		GLuint shadowmap_hight;
};

