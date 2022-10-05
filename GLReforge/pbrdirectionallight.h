#pragma once
#include "shader.h"

#define MAX_SUPPORTED_LIGHT  100
class pbrdirectionallight : public shader
{
protected:
	pbrdirectionallight();

public:
	/* delete the copy constractor*/
	pbrdirectionallight(const pbrdirectionallight&) = delete;

	/* delete the move constractor */
	pbrdirectionallight(pbrdirectionallight&&) = delete;

	/* delete the assing constractor */
	pbrdirectionallight& operator=(const pbrdirectionallight&) = delete;

	/* delete the move assing operator */
	pbrdirectionallight& operator=(const pbrdirectionallight&&) = delete;

	/* create instance of this singelton screen class since we need one main componet
	*  this is a thread safe implementation
	*/
	static pbrdirectionallight& get_instance() {
		static pbrdirectionallight instance;
		return instance;
	}

	void uniforms_update(camera* cam, const mat4x4& obj_transform,
		std::vector<lightsource*> lights) override;
};

