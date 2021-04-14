//
// Created by dbrent on 3/13/21.
//

#include "common.h"
#include "../game.h"
#include "../utils.h"

void animate(asset_t *asset) {
    float speed = 1.0 / asset->animations[asset->state]->speed;

    asset->animations[asset->state]->time->time = glfwGetTime();

    if (asset->animations[asset->state]->time->time -
                asset->animations[asset->state]->time->previous_time >=
        speed) {
        asset_animate(asset);
        asset->animations[asset->state]->time->previous_time = glfwGetTime();
    }
}

void add_bling(asset_t *asset, double frequency) {
    double r = mtwist_drand(game->mt);
    double t = frequency;
    if (r > t) { return; }

    float min_offset = -0.35f;
    float max_offset = 0.35f;
    asset_create(EFFECT_BLING, NULL,
                 asset->position.x + float_rand(min_offset, max_offset),
                 asset->position.y + float_rand(min_offset, max_offset), NONE,
                 true);
}