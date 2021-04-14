//
// Created by dbrent on 3/7/21.
//

#ifndef TRADESKILL_ORE_GOLD_H
#define TRADESKILL_ORE_GOLD_H

#include "../assets.h"
#include "common.h"

void ore_gold_update(asset_t *asset) {
    animate(asset);
    add_bling(asset, 0.0075);
}

void ore_gold_init(asset_t *asset) {
    asset->sprite = sprite_create(ORE_GOLD);
    asset->sprite->atlas_offset.x = 0;
    asset->sprite->atlas_offset.y = 0;
    asset->sprite->size.width = (int) game->atlas->sprite_width;
    asset->sprite->size.height = (int) game->atlas->sprite_height;
    asset->index = -1;

    asset->update = ore_gold_update;
}


#endif//TRADESKILL_ORE_GOLD_H
