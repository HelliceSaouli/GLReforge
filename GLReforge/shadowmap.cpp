#include "shadowmap.h"


shadowmap::shadowmap(std::vector<lightsource*>  _lights) {

	_lights = lights;
	for (auto light : lights) {
		if (light->is_source_cast_shadow()) {
			 // Create shadow map for that light source
			depthtextures.push_back(new texture());
			depthtextures.back()->generate_depth_texture(light->get_shadowmap_width(), light->get_shadowmap_hight());
		}
	}

}

shadowmap::~shadowmap() {

}