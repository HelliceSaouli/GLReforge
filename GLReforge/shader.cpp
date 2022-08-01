#include "shader.h"

#include <cstdlib>
shader::shader() {
	/* create the program */
	program = glCreateProgram();
	
	if (program == 0) {
		std::cout << "shader creation failed, no vaild memory location availble" << std::endl;
		exit(0);
	}
}

shader::~shader() {

}

void shader::add_vertex_shader(const std::string& src) {
	add_program(src, GL_VERTEX_SHADER);
}

void shader::add_geometry_shader(const std::string& src) {
	add_program(src, GL_GEOMETRY_SHADER);
}

void shader::add_fragement_shader(const std::string& src) {
	add_program(src, GL_FRAGMENT_SHADER);
}

void shader::add_program(const std::string& src, GLenum type) {
	GLuint shader = glCreateShader(type);
	if (shader == 0) {
		std::cout << "shader failed to add" << type << " program" << std::endl;
		exit(0);
	}
	const GLchar* source = src.c_str();
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	rendertools::gl_error_check(shader, GL_COMPILE_STATUS, GL_FALSE, "Error : shader compiling failed ..:");

	glAttachShader(program, shader);
}

void shader::compile_program() {
	/* link */
	glLinkProgram(program);
	rendertools::gl_error_check(program, GL_LINK_STATUS, GL_TRUE, "Error : shader linking failed ..:");

	/* validate */
	glValidateProgram(program);
	rendertools::gl_error_check(program, GL_VALIDATE_STATUS, GL_TRUE, "Error : invalide program ..:");
}

void shader::add_uniform(const std::string& uniform) {
	GLuint uniform_location = glGetUniformLocation(program, uniform.c_str());
	if (uniform_location == -1) {
		std::cout << "No uniform with name " << uniform << " was found " << std::endl;
		exit(0);
	}

	uniforms[uniform] = uniform_location;
}

void shader::uniform1i(const std::string& uniform, GLint i) {
	glUniform1i(uniforms[uniform], i);
}

void shader::uniform1f(const std::string& uniform, GLfloat f) {
	glUniform1f(uniforms[uniform], f);
}

void shader::uniform3f(const std::string& uniform, vec3 v) {
	glUniform3f(uniforms[uniform], v.x, v.y, v.z);
}

void shader::uniformMatrix4(const std::string& uniform, mat4x4 m) {
	glUniformMatrix4fv(uniforms[uniform], 1, GL_FALSE, m.mat);
}

void shader::bind_shader() {
	glUseProgram(program);
}