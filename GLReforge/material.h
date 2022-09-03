#pragma once
#include "GL/glew.h"

#include "vec3.h"
#include "texture.h"

#include "camera.h"
#include "lightsource.h"
#include "pointlight.h"

#include "shader.h"

#include <vector>
#include <string>

/* pbr material */
class material
{
	public:
		material();
		~material();

	public:
		void init_shader();
		void bind_material_shader();
		void update_material_uniform_shader(camera* cam, const mat4x4& obj_transform,
			std::vector<lightsource*> light);

		void set_albedo_texture(const std::string& image_name);
		void material_use_albedo_texture();
	private:
		/* TODO : implement a cleaning up function where you free texture from GPU memory */
		/*  mesh can have multiple albedo this is not supported */

		/* pbt texture map */
		texture* albedomap;
		texture* metalicmap;
		texture* specularmap;
		texture* roughnessmap;
		texture* ambeintocclusionmap;
		texture* normalmap;

		/* pbr single values */
		vec3 albedo;
		GLfloat metalic;
		GLfloat specular;
		GLfloat roughness;
		GLfloat ambeintocclusion;
		
		/* the shader that uses material */
		shader* material_shader;
		GLboolean is_default_loaded;
};

