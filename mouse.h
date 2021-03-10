//
// Created by dbrent on 3/2/21.
//

#ifndef TRADESKILL_MOUSE_H
#define TRADESKILL_MOUSE_H

#include "globals.h"

void show_cursor();

void hide_cursor();

GLFWcursor *custom_cursor();

void cursor_position_callback(GLFWwindow *window, double x_pos, double y_pos);

void scroll_callback(GLFWwindow *window, double x_offset, double y_offset);

void mouse_button_callback(GLFWwindow *gl_window, int button, int action,
                           int mods);

#endif//TRADESKILL_MOUSE_H
