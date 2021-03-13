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
typedef void (*asset_tick_f)(asset_t *);

typedef struct {
    float x;
    float y;
    sprite_type_e type;
    asset_t *asset;
} asset_add_queue_entry_t;

typedef struct {
    float x;
    float y;
} asset_position_t;

struct asset_t {
    sprite_t *sprite;
    sprite_t *parent;
    bool visible;
    float z;
    int index;
    asset_position_t position;
    asset_init_f init;
    asset_update_f update;
    asset_tick_f tick;
    asset_render_f render;
    animation_t **animations;
    animation_type_e state;
    int animation_count;
};

typedef struct {
    asset_position_t position;
    texture_uv_t uv;
} vertex_t;

void assets_init();

void assets_destroy();

asset_t *asset_create(sprite_type_e type);

void asset_add(sprite_type_e type);

void asset_remove(asset_t *asset);

void asset_animation_add(asset_t *asset, animation_t *animation);

void asset_animate(asset_t *asset);

void asset_set_active_animation(asset_t *asset, animation_type_e type);

void asset_destroy(asset_t *asset);

asset_t *asset_get_by_index(int id);

void *asset_process_add_queue();
void *asset_process_rem_queue();

#endif//TRADESKILL_ASSETS_H
