//
// Created by dbrent on 3/2/21.
//

#include "game.h"
#include "logger.h"

#include <stdio.h>
#include <stdlib.h>

game_t *game;

void game_init(char *name) {
    game = malloc(sizeof(game_t));
    if (game == NULL) {
        logline(ERROR, "Could not initialize game");
        exit(-1);
    }

    window_init(name);
    timer_init();
    state_init();
}

void game_destroy() {
    state_destroy();
    timer_destroy();
    window_destroy();

    if (game != NULL) {
        free(game);
        game = NULL;
    }
}
