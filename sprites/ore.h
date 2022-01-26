//
// Created by brent on 4/22/2021.
//

#ifndef TRADESKILL_ORE_H
#define TRADESKILL_ORE_H

#include "../assets.h"
#include <stdlib.h>

static void ore_update(asset_t *asset) { asset_move(asset, E); }

static void ore_init(asset_t *asset) {
    asset->sprite = sprite_create(ORE_COPPER);
    int r = (rand() % 200);
    int rg = 0;
    if (r == 0) { rg = (rand() % 5); }

    asset->sprite->atlas_offset.x = rg;
    asset->sprite->atlas_offset.y = 0;
    asset->sprite->size.width = 16;
    asset->sprite->size.height = 16;
    asset->speed = 0.1f;
    asset->index = -1;

    asset->update = ore_update;
}

#endif//TRADESKILL_ORE_H
