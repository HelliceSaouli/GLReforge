#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "GL/glew.h"
class resouceloader
{
public:
	static std::string load_shader_source(const std::string& path);
};

