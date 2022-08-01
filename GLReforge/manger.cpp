#include "manger.h"
#include "rendertools.h"
#include "resouceloader.h"
#include "vertex.h" // just for testing

#include <iostream>
#include <vector>
#include <string>

void manger::engine_initialize() {

	/* create the screen. more initialization stuff will be here*/
	is_engine_running = GL_FALSE;
	can_engine_render = GL_FALSE;

	screen& win = screen::get_instance();
	if (!win.setup_screen_window(1024, 720, (char*)"GL Reforge Engine")) {
		std::cout << "Engine failed to start" << std::endl;
		return ;
	}
	rendertools::init_gl_states();
	rendertools::opengl_info();

	/* initialize scene testing */
	test_mesh.create_geometry_buffer();
	std::vector<vertex> buffer;
	buffer.push_back(vertex(-1.0f, -1.0f, 0.0f));
	buffer.push_back(vertex( 0.0f,  1.0f, 0.0f));
	buffer.push_back(vertex( 1.0f, -1.0f, 0.0f));
	test_mesh.glmemcpy(buffer);

	/* this stupid */
	
	std::string vertex_src    = resouceloader::load_shader_source("basicprogram.vert");
	std::string fragement_src = resouceloader::load_shader_source("basicprogram.frag");
	test_shader = new shader();
	test_shader->add_vertex_shader(vertex_src);
	test_shader->add_fragement_shader(fragement_src);
	test_shader->compile_program();
	test_shader->add_uniform("scale");
	
}

void manger::engine_start() {

	/* if the engine is running do nothing */
	if (is_engine_running) {
		return; 
	}

	engine_run();
}

void manger::engine_stop() {
	if (!is_engine_running) {
		return;
	}
	is_engine_running = GL_FALSE;
	engine_clean_destroy();
}

void manger::engine_run() {
	is_engine_running = GL_TRUE;
	screen& win = screen::get_instance();

	/* start timing */
	GLdouble last_time = glfwGetTime();
	GLdouble unprocessed_time = 0.0;
	GLint frames = 0;
	GLdouble frame_counter = 0.0;

	while (is_engine_running) {
		
		/* handel time and frame data */
		GLdouble start_time  = glfwGetTime();
		GLdouble passed_time = start_time - last_time;
		last_time = start_time;
		unprocessed_time += passed_time;
		frame_counter += passed_time;

		can_engine_render = GL_FALSE;
		/* handel interactivy and mybe GUI ?
		   i'm caping the frame rate to 60
		*/
		while (unprocessed_time > FRAMCAP) {
			unprocessed_time -= FRAMCAP;

			/* event handling */
			glfwPollEvents();
			if (win.is_close_requested()) {
				engine_stop();
			}
			// handle inputs and do updates
			engine_input_handel();
			test_shader->uniform1f("scale", 0.5f);

			if (frame_counter >= 1.0) {
				std::cout << " FPS : " << frames << std::endl;
				frames = 0;
				frame_counter = 0.0;
			}
			can_engine_render = GL_TRUE;
		}

		/* render only if possible */
		if (can_engine_render) {
			engine_render();
			frames++;
		}
		
	}

}
void manger::engine_render() {

	screen& win = screen::get_instance();
	rendertools::clear_screen();
	test_shader->bind_shader();
	test_mesh.mesh_draw();
	win.refresh();
}

void manger::engine_clean_destroy() {
	
	// despose of the screen
	screen& win = screen::get_instance();
	win.screen_destroy();

}

void manger::engine_input_handel() {

	screen& win = screen::get_instance();
	if (win.is_key_pressed(GLFW_KEY_LEFT)) {
		std::cout << "Left Key is pressed " << std::endl;
		GLdouble x, y;
		win.follow_mouse(&x, &y);
		std::cout << "mouse is at position : (" << x << ", " << y << ")" << std::endl;
	}
	if (win.is_key_pressed(GLFW_KEY_RIGHT)) {
		std::cout << "Right Key is pressed " << std::endl;
	}

}