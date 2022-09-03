#pragma once
/* this is not a defnitive pbr, it will only have one directional light*/

#include "shader.h"
class basicpbr :public shader
{
protected:
	basicpbr();

public:
	/* delete the copy constractor*/
	basicpbr(const basicpbr&) = delete;

	/* delete the move constractor */
	basicpbr(basicpbr&&) = delete;

	/* delete the assing constractor */
	basicpbr& operator=(const basicpbr&) = delete;

	/* delete the move assing operator */
	basicpbr& operator=(const basicpbr&&) = delete;

	/* create instance of this singelton screen class since we need one main componet
	*  this is a thread safe implementation
	*/
	static basicpbr& get_instance() {
		static basicpbr instance;
		return instance;
	}

	void uniforms_update(camera* cam, const mat4x4& obj_transform,
		std::vector<lightsource*> lights) override;

};

