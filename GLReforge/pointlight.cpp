#include "pointlight.h"

pointlight::pointlight(GLfloat c, GLfloat l, GLfloat q, GLfloat r) {
	 constant = c;
	 linear = l;
	 quadratic = q;
	 max_range = r;
}

pointlight::~pointlight() {

}

void pointlight::update() {

}