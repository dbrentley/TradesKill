//
// Created by dbrent on 3/2/21.
//

#include "state.h"
#include "game.h"
#include "stdlib.h"
#include "utils.h"


void state_init() {
    game->state = malloc(sizeof(state_t));
    checkm(game->state);
}

void state_destroy() { ffree(game->state, "16 state.c"); }
