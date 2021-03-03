//
// Created by dbrent on 3/2/21.
//

#include "mouse.h"
#include "game.h"
#include "globals.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void hide_cursor() {
    glfwSetInputMode(game->window->gl_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void show_cursor() {
    glfwSetInputMode(game->window->gl_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

GLFWcursor *custom_cursor() {
    unsigned char cursor_pixels[16 * 16 * 4];
    memset(cursor_pixels, 0xff, sizeof(cursor_pixels));
    GLFWimage cursor_image;
    cursor_image.width = 16;
    cursor_image.height = 16;
    cursor_image.pixels = cursor_pixels;

    GLFWcursor *cursor = glfwCreateCursor(&cursor_image, 0, 0);
    if (cursor == NULL) {
        fprintf(stderr, "Could not create cursor\n");
        exit(-1);
    }
    glfwSetCursor(game->window->gl_window, cursor);
    return cursor;
}

void cursor_position_callback(GLFWwindow *gl_window, double x_pos, double y_pos) {
    if (x_pos < 0) {
        x_pos = 0;
    }
    if (x_pos > game->window->width) {
        x_pos = game->window->width;
    }
    if (y_pos < 0) {
        y_pos = 0;
    }
    if (x_pos > game->window->height) {
        x_pos = game->window->height;
    }
    game->window->mouse_x = x_pos;
    game->window->mouse_y = y_pos;
}

void scroll_callback(GLFWwindow *gl_window, double x_offset, double y_offset) {
    game->window->scroll_x_offset = x_offset;
    game->window->scroll_y_offset = y_offset;
    if (y_offset == -1.0f) {
        //        if (game_state->window_state->zoom < 30.0f) {
        //        game_state->window_state->zoom += 1.0f;
        //        }
    } else {
        //        if (game_state->window_state->zoom > 1.0f) {
        //        game_state->window_state->zoom -= 1.0f;
        //        }
    }
    game->window->update_aspect = true;
}
