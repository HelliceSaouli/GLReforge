#pragma once

#include "GL/glew.h"

#include "vec3.h"
#include "quaternion.h"
#include "mat4x4.h"

class camera
{
	public:
		camera();
		~camera();

	public:
		void set_camera_projection(GLfloat fov, GLfloat aratio, GLfloat near, GLfloat far);

		mat4x4 get_projection()const {
			return projection;
		}

	private:
		mat4x4 projection;
};

