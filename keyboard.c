//
// Created by dbrent on 3/2/21.
//

#include "keyboard.h"
#include "game.h"
#include "globals.h"
#include "state.h"
#include "utils.h"

void keyboard_event(GLFWwindow *gl_window, int key, int scancode, int action,
                    int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        game->window->should_close = true;
    }
    if (key == GLFW_KEY_A && action == GLFW_PRESS) {}
    if (key == GLFW_KEY_B && action == GLFW_PRESS) {}
}