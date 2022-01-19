//
// Created by dbrent on 3/2/21.
//

#ifndef TRADESKILL_WINDOW_H
#define TRADESKILL_WINDOW_H

#include "globals.h"

#include <stdbool.h>

typedef struct {
    int width;
    int height;
} resize_event_t;

typedef struct {
    int width;
    int height;
    double mouse_x;
    double mouse_y;
    double scroll_x_offset;
    double scroll_y_offset;
    bool update_aspect;
    bool should_resize;
    bool should_close;
    float zoom;
    float aspect;
    resize_event_t resize_event;
    mat4x4 mvp;
    GLFWwindow *gl_window;
} window_t;

void window_init(char *title);

void set_aspect(int width, int height);

void window_destroy();


#endif//TRADESKILL_WINDOW_H
