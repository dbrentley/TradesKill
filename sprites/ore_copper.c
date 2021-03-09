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

    asset->init = ore_copper_init;
    asset->update = ore_copper_update;
    asset->render = ore_copper_render;
}

void ore_copper_update(asset_t *asset) {}

void ore_copper_render(asset_t *asset) {}
