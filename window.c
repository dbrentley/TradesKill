//
// Created by dbrent on 3/2/21.
//

#include "window.h"
#include "game.h"
#include "globals.h"
#include "keyboard.h"
#include "state.h"
#include "stdio.h"

#include <stdlib.h>

void set_aspect(int width, int height) {
    float aspect = (float) width / (float) height;
    glViewport(0, 0, width, height);
    gluOrtho2D(0.0f, (float) width, (float) height, 0.0f);
    float zoom = game->window->zoom;

    mat4x4 m, p;
    mat4x4_identity(m);
    mat4x4_ortho(p, -aspect * zoom, aspect * zoom, -zoom, zoom, 1.0f, -1.0f);
    mat4x4_mul(game->window->mvp, p, m);

    game->window->width = width;
    game->window->height = height;
    game->window->aspect = aspect;
    game->window->update_aspect = true;
}

void window_close_callback(GLFWwindow *gl_window) {
    game->window->should_close = true;
}

void error_callback(int error, const char *description) {
    printf("Error: %s\n", description);
}

void resize_callback(GLFWwindow *gl_window, int width, int height) {
    game->window->should_resize = true;
    resize_event_t resize_event;
    resize_event.width = width;
    resize_event.height = height;
    game->window->resize_event = resize_event;
}

void window_init(char *title) {
    if (!glfwInit()) {
        printf("Could not initialize GLFW\n");
        exit(-1);
    }

    game->window = malloc(sizeof(window_t));
    if (game->window == NULL) {
        printf("Could not allocate memory for window\n");
        exit(-1);
    }

    game->window->gl_window = malloc(sizeof(GLFWwindow *));
    if (game->window->gl_window == NULL) {
        printf("Could not allocate memory for GL window\n");
        exit(-1);
    }

    game->window->width = DEFAULT_WIDTH;
    game->window->height = DEFAULT_HEIGHT;
    game->window->zoom = 1.0f;
    game->window->should_close = false;
    game->window->should_resize = false;
    game->window->update_aspect = false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    // glfwWindowHint(GLFW_SAMPLES, 4); // anti-alias

    game->window->gl_window = glfwCreateWindow(
            game->window->width, game->window->height, title, NULL, NULL);
    if (!game->window->gl_window) {
        glfwTerminate();
        printf("Could not create window\n");
        exit(-1);
    }

    // keyboard
    glfwSetKeyCallback(game->window->gl_window, keyboard_event);

    // mouse
    //glfwSetCursorPosCallback(window, cursor_position_callback);
    //glfwSetScrollCallback(window, scroll_callback);

    // window
    glfwSetErrorCallback(error_callback);
    glfwSetWindowCloseCallback(game->window->gl_window, window_close_callback);
    glfwSetFramebufferSizeCallback(game->window->gl_window, resize_callback);
    glfwMakeContextCurrent(game->window->gl_window);
    glfwSwapInterval(1);// v-sync

    glewExperimental = GL_TRUE;
    glewInit();

    const GLubyte *renderer = glGetString(GL_RENDERER);// get renderer string
    const GLubyte *version = glGetString(GL_VERSION);  // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    // enable depth testing
    glEnable(GL_DEPTH_TEST);
    // depth-testing interprets a smaller value as "closer"
    glDepthFunc(GL_LESS);
}

void window_destroy() {
    if (game->window != NULL) {
        if (game->window->gl_window != NULL) {
            free(game->window->gl_window);
            game->window->gl_window = NULL;
        }
        free(game->window);
    }
}