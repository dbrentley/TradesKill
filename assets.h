//
// Created by dbrent on 3/7/21.
//

#ifndef TRADESKILL_ASSETS_H
#define TRADESKILL_ASSETS_H

#include "animation.h"
#include "atlas.h"
#include "sprite.h"

typedef struct asset_t asset_t;

typedef void (*asset_init_f)(asset_t *);
typedef void (*asset_update_f)(asset_t *);
typedef void (*asset_render_f)(asset_t *);

struct asset_t {
    sprite_t *sprite;
    asset_init_f init;
    asset_update_f update;
    asset_render_f render;
    animation_t **animations;
};


int assets_init();

void assets_destroy();

#endif//TRADESKILL_ASSETS_H
