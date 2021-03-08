//
// Created by dbrent on 3/7/21.
//

#ifndef TRADESKILL_ANIMATION_H
#define TRADESKILL_ANIMATION_H

typedef enum {
    WALK,
    RUN,
    IDLE,
    ATTACK,
    DODGE,
    DEATH
} animation_type_e;

typedef struct {
    animation_type_e anim_type;
    int frames;
    float delay;
} animation_t;

animation_t *animation_create(animation_type_e type);

void animation_destroy(animation_t *animation);

#endif//TRADESKILL_ANIMATION_H
