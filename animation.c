//
// Created by dbrent on 3/7/21.
//

#include "animation.h"
#include "game.h"
#include "utils.h"

#include <stdlib.h>

animation_t *animation_create(animation_type_e type, sprite_t *sprite,
                              int frame_total, float speed) {
    animation_t *anim = malloc(sizeof(animation_t));
    checkm(anim);

    anim->type = type;
    anim->current_frame = 0;
    anim->frame_atlas_offset_x = sprite->atlas_offset.x;
    anim->frame_atlas_offset_y = sprite->atlas_offset.y;
    anim->speed = speed;
    anim->frame_total = frame_total;

    animation_time_t time;
    time.delta = 0;
    time.time = glfwGetTime();
    time.start_time = 0;
    time.end_time = glfwGetTime();
    anim->time = time;


    anim->frames = malloc(frame_total * 8 * sizeof(float));
    checkm(anim->frames);

    float psw = game->atlas->pixel_size_width * game->atlas->sprite_width;
    float psh = game->atlas->pixel_size_height * game->atlas->sprite_height;

    for (int x = 0; x < frame_total * 8; x += 8) {
        // ll
        anim->frames[x + 0] =
                (float) (anim->frame_atlas_offset_x + anim->current_frame) *
                psw;
        anim->frames[x + 1] = (float) anim->frame_atlas_offset_y * psh + psh;
        // lr
        anim->frames[x + 2] =
                (float) (anim->frame_atlas_offset_x + anim->current_frame) *
                        psw +
                psw;
        anim->frames[x + 3] = (float) anim->frame_atlas_offset_y * psh + psh;
        // ur
        anim->frames[x + 4] =
                (float) (anim->frame_atlas_offset_x + anim->current_frame) *
                        psw +
                psw;
        anim->frames[x + 5] = (float) anim->frame_atlas_offset_y * psh;
        // ul
        anim->frames[x + 6] =
                (float) (anim->frame_atlas_offset_x + anim->current_frame) *
                psw;
        anim->frames[x + 7] = (float) anim->frame_atlas_offset_y * psh;
        anim->current_frame++;
    }

    anim->current_frame = 0;
    return anim;
}

void animation_destroy(animation_t *animation) {
    if (animation != NULL) {
        ffree(animation->frames, "69 animation.c");
        ffree(animation, "70 animation.c");
    }
}
