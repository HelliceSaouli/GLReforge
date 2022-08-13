#include "manger.h"
#include "rendertools.h"
#include "resouceloader.h"
#include "vertex.h" // just for testing
#include "simpleshader.h" // for testing

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
	//test_mesh.create_geometry_buffer();
	//std::vector<vertex> buffer;
	//std::vector<GLuint> indices;
	//buffer.push_back(vertex(-1.0f, -1.0f, 0.0f));
	//indices.push_back(0);
	//buffer.push_back(vertex( 0.0f,  1.0f, 0.0f));
	//indices.push_back(1);
	//buffer.push_back(vertex( 1.0f, -1.0f, 0.0f));
	//indices.push_back(2);
	//test_mesh.glmemcpy(buffer, indices);

	GLfloat aspecration = (GLfloat)(win.get_window_width() / win.get_window_hight());
	test_camera.set_camera_projection(70.0f, aspecration, 0.1f, 1000.0f);

	if (!resouceloader::load_mesh("models/test_model.gltf", &test_mesh)){
		exit(0);
	}
	test_material = new material();

	/* this stupid */
	
	//std::string vertex_src    = resouceloader::load_shader_source("basicprogram.vert");
	//std::string fragement_src = resouceloader::load_shader_source("basicprogram.frag");
	//test_shader = new shader();
	//test_shader->add_vertex_shader(vertex_src);
	//test_shader->add_fragement_shader(fragement_src);
	//test_shader->compile_program();
	//test_shader->add_uniform("transfrom_matrix");
	//test_shader->add_uniform("projection_matrix");
	//test_shader->add_uniform("camera_matrix");

	/* initiate shader */
	simpleshader& test_simpleshader = simpleshader::get_instance();

	test_global = 0.0f;
	test_transform.rotation(0.0f, 180.0f, 0.0f);
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
			engine_update();
			

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
	simpleshader& test_simpleshader = simpleshader::get_instance();
	rendertools::clear_screen();
	test_simpleshader.bind_shader();
	test_simpleshader.uniforms_update(test_camera.get_projection(), test_camera.get_transform(), 
									  test_transform.get_transform(), test_material);
	test_mesh.mesh_draw();
	win.refresh();
}

void manger::engine_clean_destroy() {
	
	// despose of the screen
	screen& win = screen::get_instance();
	win.screen_destroy();

}

void manger::engine_update() {
	test_global += 1.0f / 60.0f;
	test_transform.translate(sin(test_global), 0.0f, 10.0f);
	// test_transform.scale(sin(test_global), sin(test_global), sin(test_global));
	test_camera.camera_update_transform();
}


void manger::engine_input_handel() {

	screen& win = screen::get_instance();
	/* i shoud move this to camera and just call camera.input() */
	if (win.is_key_pressed(GLFW_KEY_LEFT)) {
		vec3 left = test_camera.get_camera_left();
		test_camera.move_camera(left, 0.5f);
	}
	if (win.is_key_pressed(GLFW_KEY_RIGHT)) {
	    vec3 right = test_camera.get_camera_right();
		test_camera.move_camera(right, 0.5f);
	}

	if (win.is_key_pressed(GLFW_KEY_UP)) {
		test_camera.move_camera(test_camera.camera_forward, 0.5f);
	}
	if (win.is_key_pressed(GLFW_KEY_DOWN)) {
		test_camera.move_camera(test_camera.camera_forward * (-1.0f), 0.5f);
	}
}