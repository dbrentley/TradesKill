//
// Created by dbrent on 3/2/21.
//

#include "timer.h"
#include "game.h"
#include "stdlib.h"
#include "utils.h"

#include <pthread.h>
#include <stdio.h>

static void *debug_thread() {
    printf("Cores: %d, Threads: %d, HyperThreading: %s\n",
           game->system.cpu.n_cores, game->system.cpu.n_threads,
           game->system.cpu.hyperthreading ? "Yes" : "No");

    printf("FPS: %i, FT: %f, Assets: %d, Mouse: %f, %f, Zoom: %f\n",
           game->timer->fps, game->timer->delta, game->assets_count,
           game->window->mouse_x, game->window->mouse_y, game->window->zoom);
    printf("up: %f, down: %f, left: %f, right: %f\n", game->viewport_bounds.up,
           game->viewport_bounds.down, game->viewport_bounds.left,
           game->viewport_bounds.right);
}

void timer_init() {
    game->timer = malloc(sizeof(game_timer_t));
    checkm(game->timer);

    game->timer->frame_count = 0;
    game->timer->fps = 0;
    game->timer->delta = 0;
    game->timer->end_time = 0;
    game->timer->start_time = 0;
    game->timer->time = 0;
    game->timer->previous_time = glfwGetTime();
}

void timer_start() {
    game->timer->time = glfwGetTime();
    game->timer->start_time = game->timer->time;
}

void timer_end() {
    game->timer->end_time = glfwGetTime();
    game->timer->frame_count++;
    game->timer->delta = game->timer->end_time - game->timer->start_time;

    if (game->timer->time - game->timer->previous_time >= 1.0) {
        game->timer->fps = game->timer->frame_count;
        game->timer->frame_count = 0;
        game->timer->previous_time = game->timer->time;
#ifdef DEBUG_ON
        pthread_t debug_thread_id;
        pthread_create(&debug_thread_id, NULL, debug_thread, NULL);
#endif
    }
}

void timer_destroy() { ffree(game->timer, "41 timer.c"); }