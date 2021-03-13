//
// Created by dbrent on 3/2/21.
//

#include "window.h"
#include "game.h"
#include "keyboard.h"
#include "logger.h"
#include "mouse.h"
#include "state.h"
#include "stdio.h"
#include "utils.h"

#include <stdlib.h>

void set_aspect(int width, int height) {
    float aspect = (float) width / (float) height;
    glViewport(0, 0, width, height);
    gluOrtho2D(0.0f, (float) width, (float) height, 0.0f);
    game->window->width = width;
    game->window->height = height;
    game->window->aspect = aspect;
    float zoom = game->window->zoom;

    mat4x4 m, p;
    mat4x4_identity(m);
    mat4x4_ortho(p, -aspect * zoom, aspect * zoom, -zoom, zoom, 1.0f, -1.0f);
    mat4x4_mul(game->window->mvp, p, m);

    game->window->update_aspect = true;
}

void window_close_callback(GLFWwindow *gl_window) {
    game->window->should_close = true;
}

void error_callback(int error, const char *description) {
    logline(ERROR, "Error: %s", description);
}

void resize_callback(GLFWwindow *gl_window, int width, int height) {
    game->window->should_resize = true;
    resize_event_t resize_event;
    resize_event.width = width;
    resize_event.height = height;
    game->window->resize_event = resize_event;
    set_aspect(width, height);
}

void window_init(char *title) {
    if (!glfwInit()) {
        logline(ERROR, "Could not initialize GLFW");
        exit(-1);
    }

    game->window = malloc(sizeof(window_t));
    if (game->window == NULL) {
        logline(ERROR, "Could not allocate memory for window");
        exit(-1);
    }

    game->window->gl_window = malloc(sizeof(GLFWwindow *));
    if (game->window->gl_window == NULL) {
        logline(ERROR, "Could not allocate memory for GL window");
        exit(-1);
    }

    game->window->width = DEFAULT_WIDTH;
    game->window->height = DEFAULT_HEIGHT;
    game->window->zoom = 5.0f;
    game->window->should_close = false;
    game->window->should_resize = false;
    game->window->update_aspect = false;
    game->window->mouse_x = 0.0;
    game->window->mouse_y = 0.0;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    //glfwWindowHint(GLFW_SAMPLES, 4); // anti-alias

    game->window->gl_window = glfwCreateWindow(
            game->window->width, game->window->height, title, NULL, NULL);
    if (!game->window->gl_window) {
        glfwTerminate();
        logline(ERROR, "Could not create window");
        exit(-1);
    }

    // keyboard
    glfwSetKeyCallback(game->window->gl_window, keyboard_event);

    // mouse
    glfwSetCursorPosCallback(game->window->gl_window, cursor_position_callback);
    glfwSetScrollCallback(game->window->gl_window, scroll_callback);
    glfwSetMouseButtonCallback(game->window->gl_window, mouse_button_callback);

    // window
    glfwSetErrorCallback(error_callback);
    glfwSetWindowCloseCallback(game->window->gl_window, window_close_callback);
    glfwSetFramebufferSizeCallback(game->window->gl_window, resize_callback);
    glfwMakeContextCurrent(game->window->gl_window);
    glfwSwapInterval(1);// v-sync

    glewExperimental = GL_TRUE;
    glewInit();

    const GLubyte *renderer = glGetString(GL_RENDERER);// get render string
    const GLubyte *version = glGetString(GL_VERSION);  // version as a string
    logline(INFO, "Renderer: %s", renderer);
    logline(INFO, "OpenGL version supported %s", version);

    // disable depth testing
    glDisable(GL_DEPTH_TEST);

    // enable blending for alpha
    //http://www.andersriggelsen.dk/glblendfunc.php
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);

    // depth-testing interprets a smaller value as "closer"
    glDepthFunc(GL_LESS);

    glClearColor(0.169f, 0.169f, 0.169f, 0.1f);

    set_aspect(DEFAULT_WIDTH, DEFAULT_HEIGHT);
}

void window_destroy() {
    ffree(game->window->gl_window);
    ffree(game->window);
}