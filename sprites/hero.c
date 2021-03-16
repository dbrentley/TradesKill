//
// Created by dbrent on 3/14/21.
//

#include "hero.h"
#include "../game.h"

void hero_init(asset_t *asset) {
    asset->sprite = sprite_create(ORE_COPPER);
    asset->sprite->size.width = (int) game->atlas->sprite_width;
    asset->sprite->size.height = (int) game->atlas->sprite_height;

    asset->update = hero_update;
    asset->animations[IDLE_S] =
            animation_create(IDLE_S, asset->sprite, 1, 0, 3, 1.0f);
    asset->animations[WALK_E] =
            animation_create(WALK_E, asset->sprite, 2, 1, 3, 0.9f);
    asset->animations[WALK_W] =
            animation_create(WALK_W, asset->sprite, 2, 1, 4, 0.9f);
}

void hero_update(asset_t *asset) {
    asset->animations[asset->state]->time->time = glfwGetTime();

    // walk
    if (asset->animations[asset->state]->time->time -
                asset->animations[asset->state]->time->previous_time >=
        1.0 - asset->animations[asset->state]->speed) {
        asset_animate(asset);
        asset->animations[asset->state]->time->previous_time = glfwGetTime();
    }
    if (key_down) {
        switch (asset->state) {
            case WALK_W:
                asset_move(hero, W);
                break;
            case WALK_E:
                asset_move(hero, E);
                break;
            default:
                break;
        }
    }
}
