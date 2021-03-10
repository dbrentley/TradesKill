//
// Created by dbrent on 3/7/21.
//

#include "ore_gold.h"
#include "../game.h"

void ore_gold_init(asset_t *asset) {
    asset->sprite = sprite_create(ORE_GOLD);
    asset->sprite->atlas_offset.x = 0;
    asset->sprite->atlas_offset.y = 0;
    asset->sprite->size.width = (int) game->atlas->sprite_width;
    asset->sprite->size.height = (int) game->atlas->sprite_height;
    asset->index = -1;

    asset->init = ore_gold_init;
    asset->update = ore_gold_update;
    asset->render = ore_gold_render;
}

void ore_gold_update(asset_t *asset) {}

void ore_gold_render(asset_t *asset) {}

void ore_gold_destroy(asset_t *asset) {}