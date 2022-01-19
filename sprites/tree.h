//
// Created by brent on 4/22/2021.
//

#ifndef TRADESKILL_TREE_H
#define TRADESKILL_TREE_H

#include "../assets.h"
#include "common.h"

void tree_update(asset_t *asset) {}

void tree_init(asset_t *asset) {
    asset->sprite = sprite_create(TREE);
    asset->sprite->atlas_offset.x = 0;
    asset->sprite->atlas_offset.y = 10;
    asset->sprite->size.width = 16;
    asset->sprite->size.height = 32;
    asset->index = -1;

    asset->update = tree_update;
}

#endif//TRADESKILL_TREE_H
