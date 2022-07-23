#include "entity.h"


entity::entity(GLboolean _is_root) {
	is_root = _is_root;
}

entity::~entity() {
	//TODO
}

/* check if the this node has childrens*/
GLboolean entity::has_children()const {
	return (GLboolean)childrens.empty();
}