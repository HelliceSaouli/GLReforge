#include "screen.h"

GLboolean screen::setup_screen_window(GLint w, GLint h, GLchar* title) {
	
	width = w;
	hight = h;

	// set the window and stuff
	if (!glfwInit()) {
		return GL_FALSE;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

	/*create window*/
	window = glfwCreateWindow(width, hight, title, NULL, NULL);


	if (window == NULL) {
		glfwTerminate();
		return GL_FALSE;
	}

	/* make context*/
	glfwMakeContextCurrent(window);

	/* initialize glew */
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		glfwDestroyWindow(window);
		glfwTerminate();
		return GL_FALSE;
	}

	/* set up some options for windows inputs*/
	// glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

	return GL_TRUE;
}