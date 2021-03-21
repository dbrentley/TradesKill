//
// Created by dbrent on 3/7/21.
//

#ifndef TRADESKILL_ANIMATION_H
#define TRADESKILL_ANIMATION_H

#include "sprite.h"

typedef enum {
    WALK_N,
    WALK_E,
    WALK_S,
    WALK_W,
    RUN_N,
    RUN_E,
    RUN_S,
    RUN_W,
    IDLE_N,
    IDLE_E,
    IDLE_S,
    IDLE_W,
    ATTACK_N,
    ATTACK_E,
    ATTACK_S,
    ATTACK_W,
    DODGE_N,
    DODGE_E,
    DODGE_S,
    DODGE_W,
    DEATH,
    NONE,
    ANIMATION_TYPE_TOTAL
} animation_type_e;

typedef struct {
    double time;
    double previous_time;
    double start_time;
    double end_time;
    double delta;
} animation_time_t;

typedef struct {
    animation_type_e type;
    float *frames;
    float speed;
    int fao_x;
    int fao_y;
    int frame_total;
    int current_frame;
    animation_time_t *time;
} animation_t;

animation_t *animation_create(animation_type_e type, sprite_t *sprite,
                              int frame_total, int fao_x, int fao_y,
                              float speed);

void animation_destroy(animation_t *animation);

#endif//TRADESKILL_ANIMATION_H
