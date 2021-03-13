//
// Created by dbrent on 3/11/21.
//

#include "effect_bling.h"
#include "../game.h"

void effect_bling_init(asset_t *asset) {
    asset->sprite = sprite_create(EFFECT_BLING);
    asset->sprite->atlas_offset.x = 0;
    asset->sprite->atlas_offset.y = 2;
    asset->sprite->size.width = (int) game->atlas->sprite_width;
    asset->sprite->size.height = (int) game->atlas->sprite_height;

    asset->init = effect_bling_init;
    asset->update = effect_bling_update;
    asset->tick = effect_bling_tick;
    asset->render = effect_bling_render;

    asset->animations[IDLE] = animation_create(IDLE, asset->sprite, 7, 0.95f);
}

void effect_bling_update(asset_t *asset) {
    if (asset->animations[asset->state]->current_frame == 0) {
        if (mtwist_drand(game->mt) > 0.01) { return; }
    }

    asset_animate(asset);
}

void effect_bling_tick(asset_t *asset) {}

void effect_bling_render(asset_t *asset) {}
