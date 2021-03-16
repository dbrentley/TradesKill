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

    asset->update = effect_bling_update;

    asset->animations[IDLE_S] =
            animation_create(IDLE_S, asset->sprite, 4, 0, 2, 0.95f);
}

void effect_bling_update(asset_t *asset) {
    asset->animations[asset->state]->time->time = glfwGetTime();

    if (asset->animations[asset->state]->time->time -
                asset->animations[asset->state]->time->previous_time >=
        1.0 - asset->animations[asset->state]->speed) {
        asset_animate(asset);
        asset->animations[asset->state]->time->previous_time = glfwGetTime();
    }
}
