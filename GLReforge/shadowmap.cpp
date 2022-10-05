#include "shadowmap.h"


shadowmap::shadowmap() {

}

shadowmap::~shadowmap() {

}

void shadowmap::add_shadow_map(GLuint w, GLuint h) {
	depthtextures.push_back(new texture());
	depthtextures.back()->generate_depth_texture(w, h);
}