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
    asset->animations[IDLE_E] =
            animation_create(IDLE_E, asset->sprite, 1, 0, 3, 1.0f);
    asset->animations[WALK_E] =
            animation_create(WALK_E, asset->sprite, 2, 1, 3, 0.9f);
    asset->animations[IDLE_S] =
            animation_create(IDLE_S, asset->sprite, 1, 0, 4, 1.0f);
    asset->animations[WALK_S] =
            animation_create(WALK_S, asset->sprite, 2, 1, 4, 0.9f);
    asset->animations[IDLE_N] =
            animation_create(IDLE_N, asset->sprite, 1, 0, 5, 1.0f);
    asset->animations[WALK_N] =
            animation_create(WALK_N, asset->sprite, 2, 1, 5, 0.9f);
    asset->animations[IDLE_W] =
            animation_create(IDLE_W, asset->sprite, 1, 0, 6, 1.0f);
    asset->animations[WALK_W] =
            animation_create(WALK_W, asset->sprite, 2, 1, 6, 0.9f);
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

    if (game->keys[GLFW_KEY_A] || game->keys[GLFW_KEY_S] ||
        game->keys[GLFW_KEY_W] || game->keys[GLFW_KEY_D]) {
        // movement
        switch (game->last_key) {
            case GLFW_KEY_A:
                asset_set_active_animation(asset, WALK_W);
                asset_move(asset, W);
                break;
            case GLFW_KEY_S:
                asset_set_active_animation(asset, WALK_S);
                asset_move(asset, S);
                break;
            case GLFW_KEY_W:
                asset_set_active_animation(asset, WALK_N);
                asset_move(asset, N);
                break;
            case GLFW_KEY_D:
                asset_set_active_animation(asset, WALK_E);
                asset_move(asset, E);
                break;
            default:
                break;
        }
    } else {
        asset_set_active_animation(asset, IDLE_S);
    }
}
