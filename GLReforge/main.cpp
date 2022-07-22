#include <iostream>

#include "manger.h"
#include "defines.h"


int main() {
	
	manger& engine_manger = manger::get_instance();

	engine_manger.engine_initialize();
	engine_manger.engine_start();


	return 0;
}