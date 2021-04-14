//
// Created by dbrent on 3/8/21.
//

#ifndef TRADESKILL_ORE_COPPER_H
#define TRADESKILL_ORE_COPPER_H

#include "../assets.h"

void ore_copper_update(asset_t *asset) { asset_animate(asset); }

void ore_copper_init(asset_t *asset) {
    asset->sprite = sprite_create(ORE_GOLD);
    asset->sprite->atlas_offset.x = 1;
    asset->sprite->atlas_offset.y = 0;
    asset->sprite->size.width = (int) game->atlas->sprite_width;
    asset->sprite->size.height = (int) game->atlas->sprite_height;
    asset->index = -1;

    asset->update = ore_copper_update;
}


#endif//TRADESKILL_ORE_COPPER_H
