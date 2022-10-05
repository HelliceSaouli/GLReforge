#include "shadowmapcomp.h"


shadowmapcomp::shadowmapcomp(shadowmap* _shadows, staticmodel* _model, std::vector<lightsource*> _lights) {
	shadows = _shadows;
	model   = _model;
	lights = _lights;
}


shadowmapcomp::~shadowmapcomp() {

}

void shadowmapcomp::render() {

}

void shadowmapcomp::init_component(){

}