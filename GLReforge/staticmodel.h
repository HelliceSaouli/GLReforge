#pragma once

#include "GL/glew.h"

#include "mesh.h"
#include "material.h"

#include <vector>

/* i should just make it a structure */
class staticmodel
{
	public:
		staticmodel();
		~staticmodel();
	public:
		void add_mesh(GLuint matindx, const std::vector<vertex> &buffer, const std::vector<GLuint> &indices, GLuint indx);
		void set_albedo_texture(std::string fullpath, GLuint indx);
		void use_material_albedo(GLuint indx);
		void draw_model_part(GLuint indx);
		void init_model(GLuint nbr_of_meshs, GLuint nbr_of_matrs);
	private:
		std::vector<mesh* > model_parts;
		std::vector<material* > material_parts;
		GLuint number_of_materials;
	public:
		GLuint number_of_meshes;
		
};

