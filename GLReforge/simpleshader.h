#pragma once
#include "shader.h"


class simpleshader : public shader
{
	protected:
		simpleshader();

	public:
		/* delete the copy constractor*/
		simpleshader(const simpleshader&) = delete;

		/* delete the move constractor */
		simpleshader(simpleshader&&) = delete;

		/* delete the assing constractor */
		simpleshader& operator=(const simpleshader&) = delete;

		/* delete the move assing operator */
		simpleshader& operator=(const simpleshader&&) = delete;

		/* create instance of this singelton screen class since we need one main componet
		*  this is a thread safe implementation
		*/
		static simpleshader& get_instance() {
			static simpleshader instance;
			return instance;
		}

		 void uniforms_update(camera* cam, const mat4x4& obj_transform,
							 std::vector<lightsource*> lights) override;

		void set_ambient_light(GLfloat x, GLfloat y, GLfloat z);
	private:
		vec3 ambient_light;

};

