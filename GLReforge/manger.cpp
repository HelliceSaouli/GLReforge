#include "manger.h"
#include "rendertools.h"
#include "resouceloader.h"

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


	cam = new camera();
	GLfloat aspecration = (GLfloat)(win.get_window_width() / win.get_window_hight());
	cam->set_camera_projection(70.0f, aspecration, 0.1f, 10000.0f);
	cam->set_camera_position(0.0f, 0.0, -1.0f);
	cam->camera_look_at(vec3(0.0f, 0.0, 20.0f));

	staticmodel *test_mesh = new staticmodel();
	/* mesh */
	if (!resouceloader::load_static_model("models/sponza-gltf-pbr/Sponza.gltf", test_mesh)){
		exit(0);
	}

	
	/* light */
	pointlight* point_source = new pointlight(1.0f, 0.0014f, 0.000007f, 0.0f); /* 20 unit cover distance */
	point_source->set_position(0.0f, 50.0f, 0.0f);
	point_source->set_color(0.75f, 0.75f, 0.75f);
	std::vector<lightsource*> lights;
	lights.push_back(point_source);

	/* simple transform */
	test_global = 0.0f;
	transform* test_transform = new  transform();
   // test_transform->rotation(90.0f, 0.0, 180.0f); /* for sponza */

	/* create a mesh render */
	meshrenderer* mesh_renderer = new meshrenderer(test_mesh, lights, cam);
	mesh_renderer->init_component(); /* should it be here ?*/

	/* create  entities*/
	root = new entity(GL_TRUE);
	entity* model = new entity();

	model->set_transform(test_transform);
	model->add_entity_componenet(mesh_renderer);
	root->add_entity_child(model);
	
	// don't forget to clean all this pointers later ?
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
	rendertools::clear_screen();
	root->render();
	win.refresh();
}

void manger::engine_clean_destroy() {
	
	// despose of the screen
	screen& win = screen::get_instance();
	win.screen_destroy();

}

void manger::engine_update() {
	test_global += 1.0f / 60.0f;
	//test_transform.translate(sin(test_global), 0.0f, 10.0f);
   // test_transform.scale(sin(test_global), sin(test_global), sin(test_global));
	cam->camera_update_transform();
	root->update();
}


void manger::engine_input_handel() {

	cam->input();
	root->input();
}