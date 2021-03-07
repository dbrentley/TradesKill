//
// Created by dbrent on 3/6/21.
//

#ifndef TRADESKILL_SCENE_H
#define TRADESKILL_SCENE_H

#include "sprite.h"

#include <stdbool.h>

typedef struct {
    char *name;
    bool active;
    int sprite_count;
    int sprite_size;
    sprite_t **sprites;
} scene_t;

scene_t *scene_create(char *name);

void scene_sprite_add(scene_t *scene, sprite_t *sprite);

void scene_destroy(scene_t *scene);

#endif//TRADESKILL_SCENE_H
