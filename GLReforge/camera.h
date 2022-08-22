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
		void set_camera_position(GLfloat x, GLfloat y, GLfloat z);
		void camera_look_at(const vec3& target);
		/* move camera according to a given direction and distance*/
		void move_camera(vec3 direction, GLfloat distance);

		/* void handle camerainput free movement */
		void input();
		/* get the local right */
		vec3 get_camera_left();

		/* get the local left */
		vec3 get_camera_right();

		/* get the camera current location */
		vec3 get_camera_current_location()const {
			return camera_position;
		}

		/*rotate on x with angle in degree this like UE4*/
		void camera_add_input_pitch(GLfloat senstive, GLfloat amount);

		/*rotate on y with angle in degree this like UE4*/
		void camera_add_input_yaw(GLfloat senstive, GLfloat amount);

		/*update the transform */
		void camera_update_transform();

		mat4x4 get_projection()const {
			return projection;
		}

		mat4x4 get_transform()const {
			return camera_transform;
		}

	private:
		mat4x4 projection;
		mat4x4 camera_transform;
		vec3   camera_position;

	public:
		vec3   camera_up;
		vec3   camera_forward;
};

