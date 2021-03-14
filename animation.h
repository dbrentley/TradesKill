//
// Created by dbrent on 3/7/21.
//

#ifndef TRADESKILL_ANIMATION_H
#define TRADESKILL_ANIMATION_H

#include "sprite.h"

typedef enum { WALK, RUN, IDLE, ATTACK, DODGE, DEATH } animation_type_e;

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
    int frame_atlas_offset_x;
    int frame_atlas_offset_y;
    int frame_total;
    int current_frame;
    animation_time_t *time;
} animation_t;

/**
 *
 * @param type Type of animation
 * @param atlas_offset_x Atlas x cell offset
 * @param atlas_offset_y Atlas y cell offset
 * @param atlas_width Number of x atlas cells
 * @param atlas_height Number of y atlas cells
 * @param frame_total Total number of frames in this animation
 * @param speed Delay between frames
 * @return animation_t
 */
animation_t *animation_create(animation_type_e type, sprite_t *sprite,
                              int frame_total, float speed);

/**
 *
 * @param animation Animation to destroy
 */
void animation_destroy(animation_t *animation);

#endif//TRADESKILL_ANIMATION_H
