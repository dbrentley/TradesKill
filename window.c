//
// Created by dbrent on 3/2/21.
//

#include "window.h"
#include "game.h"
#include "keyboard.h"
#include "mouse.h"
#include "stdio.h"
#include "utils.h"

#include <stdlib.h>

#define MAX(a, b) (((a) < (b)) ? (b) : (a))
#define MIN(a, b) (((b) < (a)) ? (b) : (a))

void set_aspect(int width, int height) {
    float aspect = (float) width / (float) height;

    float hx = 0;
    float hy = 0;
    if (hero != NULL) {
        hx = hero->position.x;
        hy = hero->position.y;
    }
    glViewport(0, 0, width, height);
    gluOrtho2D(0.0f, (float) width, (float) height, 0.0f);

    game->window->width = width;
    game->window->height = height;
    game->window->aspect = aspect;
    float zoom = game->window->zoom;

    mat4x4 m, p;
    mat4x4_identity(m);
    mat4x4_ortho(p, -aspect * zoom, aspect * zoom, -zoom, zoom, 0, -1);
    mat4x4_translate_in_place(p, -hx, -hy, -1);
    //mat4x4_translate_in_place(p, (-aspect * zoom) - hx, -zoom, -1);
    //mat4x4_rotate_Z(m, m, (float) glfwGetTime() * 10.0f);
    mat4x4_mul(game->window->mvp, p, m);

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
    set_aspect(width, height);
}

GLFWmonitor *get_best_monitor(GLFWwindow *window) {
    int monitorCount;
    GLFWmonitor **monitors = glfwGetMonitors(&monitorCount);

    if (!monitors) return NULL;

    int windowX, windowY, windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    glfwGetWindowPos(window, &windowX, &windowY);

    GLFWmonitor *bestMonitor = NULL;
    int bestArea = 0;

    for (int i = 0; i < monitorCount; ++i) {
        GLFWmonitor *monitor = monitors[i];

        int monitorX, monitorY;
        glfwGetMonitorPos(monitor, &monitorX, &monitorY);

        const GLFWvidmode *mode = glfwGetVideoMode(monitor);
        if (!mode) continue;

        int areaMinX = MAX(windowX, monitorX);
        int areaMinY = MAX(windowY, monitorY);

        int areaMaxX = MIN(windowX + windowWidth, monitorX + mode->width);
        int areaMaxY = MIN(windowY + windowHeight, monitorY + mode->height);

        int area = (areaMaxX - areaMinX) * (areaMaxY - areaMinY);

        if (area > bestArea) {
            bestArea = area;
            bestMonitor = monitor;
        }
    }

    return bestMonitor;
}

void center_window(GLFWwindow *window, GLFWmonitor *monitor) {
    if (!monitor) return;

    const GLFWvidmode *mode = glfwGetVideoMode(monitor);
    if (!mode) return;

    int monitorX, monitorY;
    glfwGetMonitorPos(monitor, &monitorX, &monitorY);

    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    glfwSetWindowPos(window, monitorX + (mode->width - windowWidth) / 2,
                     monitorY + (mode->height - windowHeight) / 2);
}

void window_init(char *title) {
    if (!glfwInit()) {
        printf("Could not initialize GLFW\n");
        exit(-1);
    }

    game->window = malloc(sizeof(window_t));
    checkm(game->window);

    game->window->gl_window = malloc(sizeof(GLFWwindow *));
    checkm(game->window->gl_window);

    game->window->width = DEFAULT_WIDTH;
    game->window->height = DEFAULT_HEIGHT;
    game->window->zoom = 13.0f;
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
    //glfwWindowHint(GLFW_SAMPLES, 4);// anti-alias

    game->window->gl_window = glfwCreateWindow(
            game->window->width, game->window->height, title, NULL, NULL);
    if (!game->window->gl_window) {
        glfwTerminate();
        printf("Could not create window\n");
        exit(-1);
    }

    center_window(game->window->gl_window,
                  get_best_monitor(game->window->gl_window));

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
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    // disable depth testing
    glDisable(GL_DEPTH_TEST);

    // enable blending for alpha
    //http://www.andersriggelsen.dk/glblendfunc.php
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);

    glClearColor(0.169f, 0.169f, 0.169f, 0.1f);

    set_aspect(DEFAULT_WIDTH, DEFAULT_HEIGHT);
}

void window_destroy() {
    ffree(game->window->gl_window, "window gl_window");
    ffree(game->window, "window");
}