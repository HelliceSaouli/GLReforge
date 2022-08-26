#include "rendertools.h"

#include <iostream>
void rendertools::clear_screen() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void rendertools::init_gl_states() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//	glFrontFace(GL_CW);
//	glCullFace(GL_BACK);
//	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	// glEnable(GL_FRAMEBUFFER_SRGB);
}

void rendertools::opengl_info() {

	std::cout << "*********************************************" << std::endl;
	std::cout << "* - Opengl version : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "* - GLSL   version : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << "*********************************************" << std::endl;
}


void rendertools::gl_error_check(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage) {
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << " : '" << error << "'" << std::endl;
	}
}