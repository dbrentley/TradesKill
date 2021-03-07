//
// Created by dbrent on 3/2/21.
//

#ifndef TRADESKILL_GAME_H
#define TRADESKILL_GAME_H

#include "atlas.h"
#include "state.h"
#include "timer.h"
#include "window.h"

typedef struct {
    window_t *window;
    state_t *state;
    game_timer_t *timer;
    atlas_t *atlas;
    scene_t *current_scene;
    scene_t **scenes;
    int scene_count;
    int scene_size;
} game_t;

extern game_t *game;

void game_init(char *name);

void game_scene_add(scene_t *scene);

void game_scene_remove(scene_t *scene);

void game_destroy();

#endif//TRADESKILL_GAME_H
