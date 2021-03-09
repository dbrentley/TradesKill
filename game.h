//
// Created by dbrent on 3/2/21.
//

#ifndef TRADESKILL_GAME_H
#define TRADESKILL_GAME_H

#include "assets.h"
#include "atlas.h"
#include "state.h"
#include "timer.h"
#include "window.h"

typedef struct {
    float *vertex_buffer;
    int vertex_buffer_size;
    uint32_t *element_buffer;
    int element_buffer_size;
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
} game_gle_t;

typedef struct {
    window_t *window;
    state_t *state;
    game_timer_t *timer;
    game_gle_t *gle;
    atlas_t *atlas;
    scene_t *current_scene;
    scene_t **scenes;
    int scene_count;
    int scene_size;
    asset_t **assets;
    int assets_count;
} game_t;

extern game_t *game;

void game_init(char *name);

void game_render();

void game_scene_add(scene_t *scene);

void game_scene_remove(scene_t *scene);

void game_destroy();


#endif//TRADESKILL_GAME_H
