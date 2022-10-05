#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "screen.h"

#include "transform.h"

#include "lightsource.h"
#include "pointlight.h"
#include "sunlight.h"
#include "shadowmap.h"

#include "camera.h"
#include "staticmodel.h"

#include "entity.h"
#include "component.h"
#include "meshrenderer.h"


#define FRAMCAP 1.0/60.0

class manger
{
	protected:
		manger() = default;

	public:
		/* delete the copy constractor*/
		manger(const manger&) = delete;

		/* delete the move constractor */
		manger(manger&&) = delete;

		/* delete the assing constractor */
		manger& operator=(const manger&) = delete;

		/* delete the move assing operator */
		manger& operator=(const manger&&) = delete;

		/* create instance of this singelton screen class since we need one main componet
		*  this is a thread safe implementation
		*/
		static manger& get_instance() {
			static manger instance;
			return instance;
		}

	public:
		void engine_initialize();
		void engine_start();
		void engine_stop();
   
    private:
		void engine_run();
		void engine_render();
		void engine_clean_destroy();
		void engine_input_handel();
		void engine_update();

    private:
		GLboolean is_engine_running;
		GLboolean can_engine_render;

		/* the scene */
		entity* root;
		camera* cam;
		GLfloat test_global;
};

