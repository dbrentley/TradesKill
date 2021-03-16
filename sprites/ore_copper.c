//
// Created by dbrent on 3/8/21.
//

#include "ore_copper.h"
#include "../game.h"

void ore_copper_init(asset_t *asset) {
    asset->sprite = sprite_create(ORE_COPPER);
    asset->sprite->atlas_offset.x = 1;
    asset->sprite->atlas_offset.y = 0;
    asset->sprite->size.width = (int) game->atlas->sprite_width;
    asset->sprite->size.height = (int) game->atlas->sprite_height;

    asset->update = ore_copper_update;

    asset->animations[IDLE_S] =
            animation_create(IDLE_S, asset->sprite, 0, 1, 0, 0);
}

void ore_copper_update(asset_t *asset) { asset_animate(asset); }
