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

typedef void (*asset_update_f)(asset_t *);

typedef enum { N, E, S, W } asset_facing_e;

typedef struct {
    float x;
    float y;
    bool one_shot;
    sprite_type_e type;
    animation_type_e default_animation;
    asset_t *asset;
    char *name;
} asset_add_queue_entry_t;

typedef struct {
    float x;
    float y;
} asset_position_t;

struct asset_t {
    asset_position_t position;
    asset_facing_e facing;
    bool visible;
    bool one_shot;
    bool dirty;
    float scale;
    float velocity;
    float z;
    int index;
    char *name;
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

asset_t *asset_create(sprite_type_e type, const char *name, float x, float y,
                      animation_type_e default_animation, bool one_shot);

void asset_add(sprite_type_e type, char *name, float x, float y,
               animation_type_e default_animation, bool one_shot);

void asset_remove(asset_t *asset);

void asset_move(asset_t *asset, asset_facing_e facing);

void asset_animate(asset_t *asset);

void asset_set_active_animation(asset_t *asset, animation_type_e type);

void asset_destroy(asset_t *asset);

asset_t *asset_get_by_index(int id);
asset_t *asset_get_by_name(char *name);

void *asset_process_add_queue();
void *asset_process_rem_queue();

#endif//TRADESKILL_ASSETS_H
