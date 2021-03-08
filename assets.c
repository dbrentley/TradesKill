//
// Created by dbrent on 3/7/21.
//

#include "assets.h"
#include "logger.h"
#include "sprites/ore_gold.h"
#include "utils.h"

#include <stdlib.h>

asset_t **assets;

int assets_init() {
    sprite_type_e sprite_type_total = TOTAL;
    logline(INFO, "Initializing %d assets", sprite_type_total);

    assets = malloc(sprite_type_total * sizeof(asset_t *));
    checkm(assets);
    for (int x = 0; x < sprite_type_total; x++) {
        assets[x] = malloc(sizeof(asset_t));
        checkm(assets[x]);
    }

    ore_gold_init(assets[ORE_GOLD]);

    return sprite_type_total;
}

void assets_destroy() {
    sprite_type_e sprite_type_total = TOTAL;
    for (int x = 0; x < sprite_type_total; x++) {
        ffree(assets[x]);
    }
    ffree(assets);
}