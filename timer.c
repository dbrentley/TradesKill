//
// Created by dbrent on 3/2/21.
//

#include "timer.h"
#include "game.h"
#include "globals.h"
#include "logger.h"
#include "stdlib.h"
#include "utils.h"

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
    game->timer->frame_count++;
    game->timer->end_time = game->timer->time;
    game->timer->delta = game->timer->end_time - game->timer->start_time;

    if (game->timer->time - game->timer->previous_time >= 1.0) {
        game->timer->fps = game->timer->frame_count;
        game->timer->frame_count = 0;
        game->timer->previous_time = game->timer->time;
#ifdef DEBUG_ON
        logline(DEBUG, "FPS: %i, %d", game->timer->fps,
                queue_size(&game->queues.asset_add));
#endif
    }
}

void timer_destroy() { ffree(game->timer, "46 timer.c"); }