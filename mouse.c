//
// Created by dbrent on 3/2/21.
//

#include "mouse.h"
#include "game.h"
#include "globals.h"
#include "logger.h"

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
        logline(ERROR, "Could not create cursor");
        exit(-1);
    }
    glfwSetCursor(game->window->gl_window, cursor);
    return cursor;
}

void cursor_position_callback(GLFWwindow *gl_window, double x_pos,
                              double y_pos) {
    game->window->mouse_x = x_pos / game->window->width - 0.5;
    game->window->mouse_y = y_pos / game->window->height - 0.5;
}

void scroll_callback(GLFWwindow *gl_window, double x_offset, double y_offset) {
    game->window->scroll_x_offset = x_offset;
    game->window->scroll_y_offset = y_offset;
    if (y_offset == -1.0f) {
        if (game->window->zoom < 30.0f) { game->window->zoom += 0.5f; }
    } else {
        if (game->window->zoom > 1.0f) { game->window->zoom -= 0.5f; }
    }
    game->window->update_aspect = true;
}

void mouse_button_callback(GLFWwindow *gl_window, int button, int action,
                           int mods) {
    logline(INFO, "Mouse %f x %f", game->window->mouse_x,
            game->window->mouse_y);
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        asset_t *asset = asset_get_by_index(0);
        asset_destroy(asset);
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {

        //        asset_create((float) game->window->mouse_x,
        //                     (float) game->window->mouse_y, game->assets[ORE_GOLD]);
    }
}