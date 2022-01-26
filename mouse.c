//
// Created by dbrent on 3/2/21.
//

#include "mouse.h"
#include "game.h"
#include "tskmath.h"
#include "utils.h"

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
        printf("Could not create cursor");
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
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {}
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {}
    printf("Mouse x: %f, y: %f\n", game->window->mouse_x,
           game->window->mouse_y);

    point_2d_t p;
    p.x = hero->position.x;
    p.y = hero->position.y;

    point_2d_t q;
    q.x = game->window->mouse_x;
    q.y = game->window->mouse_y;

    vector_2d_t v;
    v.p = p;
    v.q = q;

    double pdir = get_vector_2d_direction(v);
    double pdis = get_vector_2d_distance(v);
    double pdeg = to_degrees(get_vector_2d_direction(v));

    char title[512];
    snprintf(title, 511, "dir: %lf, deg: %lf, dis: %lf, x: %lf, y: %lf\n", pdir,
             pdeg, pdis, game->window->mouse_x, game->window->mouse_y);

    //glfwSetWindowTitle(game->window->gl_window, title);
    printf("%s\n", title);
}