//
// Created by dbrent on 3/2/21.
//

#include "keyboard.h"
#include "assets.h"
#include "game.h"
#include "globals.h"
#include "state.h"
#include "utils.h"

bool key_down;

void keyboard_event(GLFWwindow *gl_window, int key, int scancode, int action,
                    int mods) {

    if (action == GLFW_PRESS) {
        game->keys[key] = 1;
        game->last_key = key;
    }
    if (action == GLFW_RELEASE) { game->keys[key] = 0; }

    //    if (action == GLFW_PRESS) { key_down = true; }
    //    if (action == GLFW_RELEASE) { key_down = false; }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        game->window->should_close = true;
    }
}