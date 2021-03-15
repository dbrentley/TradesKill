//
// Created by dbrent on 3/7/21.
//

#ifndef TRADESKILL_ANIMATION_H
#define TRADESKILL_ANIMATION_H

#include "sprite.h"

typedef enum { WALK, RUN, IDLE, ATTACK, DODGE, DEATH } animation_type_e;
typedef enum { N, NE, E, SE, S, SW, W, NW } animation_direction_e;

typedef struct {
    double time;
    double previous_time;
    double start_time;
    double end_time;
    double delta;
} animation_time_t;

typedef struct {
    animation_type_e type;
    animation_direction_e direction;
    float *frames;
    float speed;
    int frame_atlas_offset_x;
    int frame_atlas_offset_y;
    int frame_total;
    int frame_atlas_offset_x_start;
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
 * @param frame_atlas_offset_x_start Atlas frame offset from animation start
 * @param speed Delay between frames
 * @return animation_t
 */
animation_t *animation_create(animation_type_e type,
                              animation_direction_e direction, sprite_t *sprite,
                              int frame_total, int frame_atlas_offset_x_start,
                              float speed);

/**
 *
 * @param animation Animation to destroy
 */
void animation_destroy(animation_t *animation);

#endif//TRADESKILL_ANIMATION_H
