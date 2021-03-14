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

typedef enum { INIT, UPDATE, TICK } asset_event_e;

typedef void (*asset_update_f)(asset_t *);

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
    asset_position_t position;
    bool visible;
    bool one_shot;
    float z;
    int index;
    sprite_t *sprite;
    asset_update_f update;
    animation_t **animations;
    animation_type_e state;
};

typedef struct {
    asset_position_t position;
    texture_uv_t uv;
} vertex_t;

void assets_init();
void asset_init(int n);

void assets_destroy();

asset_t *asset_create(sprite_type_e type, float x, float y);

void asset_add(sprite_type_e type, float x, float y);

void asset_remove(asset_t *asset);

void asset_animation_add(asset_t *asset, animation_t *animation);

void asset_animate(asset_t *asset);

void asset_set_active_animation(asset_t *asset, animation_type_e type);

void asset_destroy(asset_t *asset);

asset_t *asset_get_by_index(int id);

void *asset_process_add_queue();
void *asset_process_rem_queue();

#endif//TRADESKILL_ASSETS_H
