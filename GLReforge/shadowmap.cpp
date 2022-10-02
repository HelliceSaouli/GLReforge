#include "shadowmap.h"


shadowmap::shadowmap(std::vector<lightsource*>  _lights) {

	_lights = lights;
	for (auto light : lights) {
		if (light->is_source_cast_shadow()) {
			 // Create shadow map for that light source
		}
	}

}


shadowmap::~shadowmap() {

}