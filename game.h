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
#include "timer.h"
#include "window.h"

typedef struct {
    float *vertex_buffer;
    uint32_t *element_buffer;
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
    int keys[348];
    int last_key;
    int assets_count;
    bool running;
    asset_t **assets;
    queues_t queues;
    mtwist *mt;
} game_t;

extern game_t *game;
extern asset_t *hero;
extern pthread_mutex_t lock;
extern bool key_down;

void game_init(char *name);

void game_render();

void game_destroy();


#endif//TRADESKILL_GAME_H
