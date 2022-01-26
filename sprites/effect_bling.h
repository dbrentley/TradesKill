//
// Created by dbrent on 3/11/21.
//

#ifndef TRADESKILL_EFFECT_BLING_H
#define TRADESKILL_EFFECT_BLING_H

#include "../assets.h"
#include "../game.h"
#include "common.h"

static void effect_bling_update(asset_t *asset) { animate(asset); }

static void effect_bling_init(asset_t *asset) {
    asset->sprite = sprite_create(EFFECT_BLING);
    asset->sprite->atlas_offset.x = 0;
    asset->sprite->atlas_offset.y = 2;
    asset->sprite->size.width = (int) game->atlas->sprite_width;
    asset->sprite->size.height = (int) game->atlas->sprite_height;

    asset->update = effect_bling_update;

    asset->animations[NONE] =
            animation_create(NONE, asset->sprite, 5, 0, 2, 50.0f);
}

#endif//TRADESKILL_EFFECT_BLING_H
