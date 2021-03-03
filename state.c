//
// Created by dbrent on 3/2/21.
//

#include "state.h"
#include "game.h"
#include "globals.h"
#include "stdio.h"
#include "stdlib.h"


void state_init() {
    game->state = malloc(sizeof(state_t));
    if (game->state == NULL) {
        printf("Could not allocate memory for window\n");
        exit(-1);
    }
}

void state_destroy() {
    if (game->state != NULL) {
        free(game->state);
        game->state = NULL;
    }
}
