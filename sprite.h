//
// Created by dbrent on 3/6/21.
//

#ifndef TRADESKILL_SPRITE_H
#define TRADESKILL_SPRITE_H

#include "atlas.h"

typedef struct sprite_t sprite_t;


typedef enum {
    ORE_COPPER,
    ORE_SILVER,
    ORE_GOLD,
    ORE_STEEL,
    ORE_TITANIUM,
    TOTAL
} sprite_type_e;

typedef struct {
    float u;
    float v;
} texture_uv_t;

typedef struct {
    int width;
    int height;
} sprite_size_t;

struct sprite_t {
    sprite_type_e type;
    sprite_size_t size;
    atlas_position_t atlas_offset;
    texture_uv_t texture;
};

sprite_t *sprite_create(sprite_type_e type);

void sprite_destroy(sprite_t *sprite);

void sprite_update(sprite_t *);

void sprite_render(sprite_t *);

#endif//TRADESKILL_SPRITE_H
