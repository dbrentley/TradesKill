//
// Created by dbrent on 3/13/21.
//

#include "common.h"
#include "../game.h"
#include "../utils.h"

void add_bling(asset_t *asset, double frequency) {
    double r = mtwist_drand(game->mt);
    double t = frequency;
    if (r > t) { return; }

    asset_t *b = asset_create(EFFECT_BLING);
    b->one_shot = true;

    float min_offset = -0.35f;
    float max_offset = 0.35f;
    b->position.x = asset->position.x + float_rand(min_offset, max_offset);
    b->position.y = asset->position.y + float_rand(min_offset, max_offset);
}