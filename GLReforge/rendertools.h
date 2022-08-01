#pragma once

#include "GL/glew.h"

#include <string>

/* I think this should be a namespace*/
class rendertools
{
	public:
		static void clear_screen();
		static void init_gl_states();
		static void opengl_info();
		static void gl_error_check(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
};

