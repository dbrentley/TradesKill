//
// Created by dbrent on 3/2/21.
//

#ifndef TRADESKILL_GAME_H
#define TRADESKILL_GAME_H

#include "assets.h"
#include "atlas.h"
#include "libmtwist/mtwist.h"
#include "queue.h"
#include "state.h"
#include "system.h"
#include "timer.h"
#include "window.h"

typedef struct {
    float up;
    float down;
    float left;
    float right;
} viewport_bounds_t;

typedef struct {
    float *vertex_buffer;
    uint32_t *element_buffer;
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
} game_gle_t;

typedef struct {
    window_t *window;
    system_t system;
    state_t *state;
    game_timer_t *timer;
    game_gle_t *gle;
    atlas_t *atlas;
    int keys[348];
    int last_key;
    int assets_total;
    int assets_count;
    int seed;
    int update_z;
    int *asset_index;
    int *viewport;
    bool running;
    float *asset_array;
    viewport_bounds_t viewport_bounds;
    asset_t **assets;
    queues_t queues;
    mtwist *mt;
} game_t;

extern game_t *game;
extern asset_t *hero;
extern pthread_mutex_t lock;
extern bool key_down;

void game_init(char *name);

void game_update();

void game_render();

void *game_asset_sort_z();

void game_destroy();


#endif//TRADESKILL_GAME_H
