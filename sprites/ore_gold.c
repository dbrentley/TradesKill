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

    asset->update = ore_gold_update;

    asset->animations[IDLE] = animation_create(IDLE, asset->sprite, 1, 0.9f);
}

void ore_gold_update(asset_t *asset) {
    asset_animate(asset);

    if (game->timer->time - game->timer->previous_time > 1.0) {
        double r = mtwist_drand(game->mt);
        if (r > 0.25) { return; }
        asset_t *b = asset_create(EFFECT_BLING);
        b->one_shot = true;
        if (r > 0.1) {
            b->position.x = asset->position.x + (float) r;
        } else {
            b->position.x = asset->position.x - (float) r;
        }
        if (r > 0.15) {
            b->position.y = asset->position.y + (float) r;
        } else {
            b->position.y = asset->position.y - (float) r;
        }
    }
}