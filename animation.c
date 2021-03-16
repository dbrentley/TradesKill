//
// Created by dbrent on 3/7/21.
//

#include "animation.h"
#include "game.h"
#include "utils.h"

#include <stdlib.h>

animation_t *animation_create(animation_type_e type, sprite_t *sprite,
                              int frame_total, int fao_x, int fao_y,
                              float speed) {
    animation_t *anim = malloc(sizeof(animation_t));
    checkm(anim);
    anim->time = malloc(sizeof(animation_time_t));
    checkm(anim->time);

    anim->type = type;
    anim->current_frame = 0;
    anim->fao_x = fao_x;
    anim->fao_y = fao_y;
    anim->speed = speed;
    anim->frame_total = frame_total;

    anim->time->delta = 0;
    anim->time->time = 0;
    anim->time->start_time = 0;
    anim->time->end_time = 0;


    anim->frames = malloc(frame_total * 8 * sizeof(float));
    checkm(anim->frames);

    float psw = game->atlas->pixel_size_width * game->atlas->sprite_width;
    float psh = game->atlas->pixel_size_height * game->atlas->sprite_height;

    for (int x = 0; x < frame_total * 8; x += 8) {
        // ll
        anim->frames[x + 0] = (float) (anim->fao_x + anim->current_frame) * psw;
        anim->frames[x + 1] = (float) anim->fao_y * psh + psh;
        // lr
        anim->frames[x + 2] =
                (float) (anim->fao_x + anim->current_frame) * psw + psw;
        anim->frames[x + 3] = (float) anim->fao_y * psh + psh;
        // ur
        anim->frames[x + 4] =
                (float) (anim->fao_x + anim->current_frame) * psw + psw;
        anim->frames[x + 5] = (float) anim->fao_y * psh;
        // ul
        anim->frames[x + 6] = (float) (anim->fao_x + anim->current_frame) * psw;
        anim->frames[x + 7] = (float) anim->fao_y * psh;
        anim->current_frame++;
    }

    anim->current_frame = 0;
    return anim;
}

void animation_destroy(animation_t *animation) {
    if (animation != NULL) {
        ffree(animation->frames, "frames animation_destroy");
        ffree(animation, "animation_destroy");
    }
}
