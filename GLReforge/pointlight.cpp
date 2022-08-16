#include "pointlight.h"

pointlight::pointlight(GLfloat c, GLfloat l, GLfloat q) {
	 constant = c;
	 linear = l;
	 quadratic = q;
}

pointlight::~pointlight() {

}

void pointlight::update() {

}