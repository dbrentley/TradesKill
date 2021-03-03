//
// Created by dbrent on 3/2/21.
//

#ifndef TRADESKILL_GAME_H
#define TRADESKILL_GAME_H

#include "state.h"
#include "timer.h"
#include "window.h"

typedef struct {
    window_t *window;
    state_t *state;
    game_timer_t *timer;
} game_t;

extern game_t *game;

void game_init(char *name);

void game_destroy();

#endif//TRADESKILL_GAME_H
