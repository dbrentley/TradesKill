//
// Created by brent on 4/7/2021.
//

#ifndef TRADESKILL_GRASS_H
#define TRADESKILL_GRASS_H

#include "../assets.h"
#include <stdlib.h>

static void grass_update(asset_t *asset) {
    // hello
}

static void grass_init(asset_t *asset) {
    asset->sprite = sprite_create(GRASS);
    int r = (rand() % 15);
    int rg = 0;
    if (r == 0) { rg = (rand() % 8); }

    asset->sprite->atlas_offset.x = rg;
    asset->sprite->atlas_offset.y = 1;
    asset->sprite->size.width = 16;
    asset->sprite->size.height = 16;
    asset->index = -1;

    asset->update = grass_update;
}

#endif//TRADESKILL_GRASS_H
