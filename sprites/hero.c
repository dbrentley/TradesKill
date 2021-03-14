//
// Created by dbrent on 3/14/21.
//

#include "hero.h"
#include "../game.h"

void hero_init(asset_t *asset) {
    asset->sprite = sprite_create(ORE_COPPER);
    asset->sprite->atlas_offset.x = 1;
    asset->sprite->atlas_offset.y = 3;
    asset->sprite->size.width = (int) game->atlas->sprite_width;
    asset->sprite->size.height = (int) game->atlas->sprite_height;

    asset->update = hero_update;

    asset->animations[IDLE] = animation_create(IDLE, asset->sprite, 4, 0.90f);
}

void hero_update(asset_t *asset) {
    asset->animations[asset->state]->time->time = glfwGetTime();

    if (asset->animations[asset->state]->time->time -
                asset->animations[asset->state]->time->previous_time >=
        1.0 - asset->animations[asset->state]->speed) {
        asset_animate(asset);
        asset->animations[asset->state]->time->previous_time = glfwGetTime();
    }
}
