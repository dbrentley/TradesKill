//
// Created by dbrent on 3/6/21.
//

#ifndef TRADESKILL_SCENE_H
#define TRADESKILL_SCENE_H

#include "sprite.h"

#include <stdbool.h>

typedef struct scene_t scene_t;

typedef void (*scene_init_f)(scene_t *);
typedef void (*scene_update_f)(scene_t *);
typedef void (*scene_render_f)(scene_t *);

struct scene_t {
    char *name;
    bool active;
    int sprite_count;
    int sprite_size;
    sprite_t **sprites;
    scene_init_f init;
    scene_update_f update;
    scene_render_f render;
};

scene_t *scene_create(char *name, scene_init_f init, scene_update_f update,
                      scene_render_f render);

void scene_sprite_add(scene_t *scene, sprite_t *sprite);

void scene_destroy(scene_t *scene);

#endif//TRADESKILL_SCENE_H
