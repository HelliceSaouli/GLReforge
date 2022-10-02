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

		void set_metalic_texture(std::string fullpath, GLuint indx);
		void use_material_metalic(GLuint indx);


		void set_roughness_texture(std::string fullpath, GLuint indx);
		void use_material_roughness(GLuint indx);

		void set_ao_texture(std::string fullpath, GLuint indx);
		void use_material_ao(GLuint indx);

		void set_normal_texture(std::string fullpath, GLuint indx);
		void use_material_normal(GLuint indx);
		
		void draw_model_part(GLuint indx);
		void init_model(GLuint nbr_of_meshs, GLuint nbr_of_matrs);

		void init_material_shader();
		void bind_material_shader(GLuint indx);
		void update_material_uniform_shader(GLuint indx, camera* cam, const mat4x4& obj_transform,
											std::vector<lightsource*> lights);

		void set_receive_shadow(GLboolean val);
		GLboolean is_receive_shadow()const;

	private:
		std::vector<mesh* > model_parts;
		std::vector<material* > material_parts;
		GLuint number_of_materials;
		GLboolean receive_shadow; /* if the model is included in the shadowmap draw call */
	public:
		GLuint number_of_meshes;
		
};

