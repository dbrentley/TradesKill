//
// Created by dbrent on 3/7/21.
//

#include "ore_gold.h"

void ore_gold_init(asset_t *asset) {
    asset->sprite = sprite_create(ORE_GOLD);
    asset->init = ore_gold_init;
    asset->update = ore_gold_update;
    asset->render = ore_gold_render;
}

void ore_gold_update(asset_t *asset) {
}

void ore_gold_render(asset_t *asset) {
}
