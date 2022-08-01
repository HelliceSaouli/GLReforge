#pragma once

#include "GL/glew.h"

#include "vec3.h"
#include "mat4x4.h"

#include "resouceloader.h"
#include "rendertools.h"

#include <unordered_map>
class shader
{
	public:
		shader();
		~shader();

	public:
		void add_vertex_shader(const std::string& src);
		void add_geometry_shader(const std::string& src);
		void add_fragement_shader(const std::string& src);
		void compile_program();

		/* uniforms */
		void add_uniform(const std::string& uniform);
		void uniform1i(const std::string& uniform, GLint i);
		void uniform1f(const std::string& uniform, GLfloat f);
		void uniform3f(const std::string& uniform, vec3 v);
		void uniformMatrix4(const std::string& uniform, mat4x4 m);
		
		void bind_shader();

	private:
		void add_program(const std::string& src, GLenum type);

	private:
		GLuint program;
		std::unordered_map<std::string, GLuint> uniforms;
};

