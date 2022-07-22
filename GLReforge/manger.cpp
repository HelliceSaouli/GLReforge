#include "manger.h"

#include <iostream>

void manger::engine_initialize() {

	/* create the screen. more initialization stuff will be here*/
	is_engine_running = GL_FALSE;
	can_engine_render = GL_FALSE;

	screen& win = screen::get_instance();
	if (!win.setup_screen_window(1024, 720, (char*)"GL Reforge Engine")) {
		std::cout << "Engine failed to start" << std::endl;
		return ;
	}

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
			engine_input_handel();

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