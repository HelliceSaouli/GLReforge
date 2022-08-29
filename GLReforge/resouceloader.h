#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include "GL/glew.h"

#include "staticmodel.h"
#include "vec3.h"
#include "vertex.h"

class resouceloader
{
public:
	static std::string load_shader_source(const std::string& path);
	static GLboolean load_static_model(const std::string& path, staticmodel* model);
	static GLubyte* load_texture(const std::string& path, GLint* width, GLint* Heigh, GLint* nrChannels);
	static void free_texture_data(GLubyte* data);
};

