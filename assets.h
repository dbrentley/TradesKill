//
// Created by dbrent on 3/7/21.
//

#ifndef TRADESKILL_ASSETS_H
#define TRADESKILL_ASSETS_H

#include "animation.h"
#include "atlas.h"
#include "sprite.h"

#include <stdbool.h>

typedef struct asset_t asset_t;

typedef void (*asset_init_f)(asset_t *);
typedef void (*asset_update_f)(asset_t *);
typedef void (*asset_render_f)(asset_t *);

typedef struct {
    float x;
    float y;
} asset_position_t;

struct asset_t {
    sprite_t *sprite;
    bool visible;
    float z;
    asset_position_t position;
    asset_init_f init;
    asset_update_f update;
    asset_render_f render;
    animation_t **animations;
};

typedef struct {
    asset_position_t position;
    texture_uv_t uv;
} vertex_t;

int assets_init();

void assets_destroy();

void asset_create(float x, float y, asset_t *asset);

#endif//TRADESKILL_ASSETS_H
