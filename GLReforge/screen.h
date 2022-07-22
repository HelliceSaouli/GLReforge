#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>
class screen
{
	protected:
		screen() = default;

	public:
		/* delete the copy constractor*/
		screen(const screen& ) = delete;

		/* delete the move constractor */
		screen(screen&&) = delete;

		/* delete the assing constractor */
		screen& operator=(const screen&) = delete;

		/* delete the move assing operator */
		screen& operator=(const screen&&) = delete;

		/* create instance of this singelton screen class since we need one screen
		*  this is a thread safe implementation
		*/
		static screen& get_instance() {
			static screen instance;
			return instance;
		}

		
		/* basicaly refreshing */
		void refresh() {
			glfwSwapBuffers(window);
		}

		/* despose */
		void screen_destroy() {
			glfwDestroyWindow(window);
			glfwTerminate();
		}

		GLboolean is_close_requested() {
			return glfwWindowShouldClose(window);
		}

		GLboolean setup_screen_window(GLint w, GLint h, GLchar* title);
		public:
			/* setters and getters for the class data*/
			GLint get_window_width()const {
				return width;
			}

			GLint get_window_hight()const {
				return hight;
			}

			void set_window_width(const GLint& w) {
				width = w;
			}

			void set_window_hight(const GLint& h) {
				hight = h;
			}

			GLboolean is_key_pressed(GLint key) {
				if (glfwGetKey(window, key) == GLFW_PRESS) {
					return GL_TRUE;
				}
				return GL_FALSE;
			}

			GLboolean is_key_released(GLint key) {
				if (glfwGetKey(window, key) == GLFW_RELEASE) {
					return GL_TRUE;
				}
				return GL_FALSE;
			}

			void follow_mouse(GLdouble* x, GLdouble* y) {
				glfwGetCursorPos(window, x, y);
			}

		private:

			/* The screen size*/
			GLint width;
			GLint hight;

			/* The actual window*/
			GLFWwindow* window;
};

