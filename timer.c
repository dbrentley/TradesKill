//
// Created by dbrent on 3/2/21.
//

#include "timer.h"
#include "game.h"
#include "globals.h"
#include "stdio.h"
#include "stdlib.h"

void timer_init() {
    game->timer = malloc(sizeof(window_t));
    if (game->timer == NULL) {
        printf("Could not allocate memory for window\n");
        exit(-1);
    }

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
    game->timer->frame_count++;
    game->timer->end_time = game->timer->time;
    game->timer->delta = game->timer->end_time - game->timer->start_time;

    if (game->timer->time - game->timer->previous_time >= 1.0) {
        game->timer->fps = game->timer->frame_count;
        game->timer->frame_count = 0;
        game->timer->previous_time = game->timer->time;
        fprintf(stderr, "FPS: %i\n", game->timer->fps);
    }
}

void timer_destroy() {
    if (game->timer != NULL) {
        free(game->timer);
        game->timer = NULL;
    }
}