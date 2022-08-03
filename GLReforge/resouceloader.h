#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include "GL/glew.h"

#include "mesh.h"
#include "vec3.h"
#include "vertex.h"

class resouceloader
{
public:
	static std::string load_shader_source(const std::string& path);
	static GLboolean load_mesh(const std::string& path, mesh* object); /* simplefunction to load mesh from file using assimp */
};

