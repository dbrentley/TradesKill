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

    float min_offset = -0.35f;
    float max_offset = 0.35f;
    asset_add(EFFECT_BLING,
              asset->position.x - 0.5f + float_rand(min_offset, max_offset),
              asset->position.y - 0.5f + float_rand(min_offset, max_offset),
              true);
}