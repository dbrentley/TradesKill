//
// Created by dbrent on 3/7/21.
//

#include "assets.h"
#include "game.h"
#include "logger.h"
#include "sprites/ore_copper.h"
#include "sprites/ore_gold.h"
#include "utils.h"

#include <stdlib.h>

int assets_init() {
    sprite_type_e sprite_type_total = TOTAL;
    logline(INFO, "Initializing %d assets", sprite_type_total);

    game->assets = malloc(sprite_type_total * sizeof(asset_t *));
    checkm(game->assets);
    for (int x = 0; x < sprite_type_total; x++) {
        game->assets[x] = malloc(sizeof(asset_t));
        checkm(game->assets[x]);
    }

    ore_gold_init(game->assets[ORE_GOLD]);
    ore_copper_init(game->assets[ORE_COPPER]);

    return sprite_type_total;
}

void asset_create(float x, float y, asset_t *asset) {
    float psw = game->atlas->pixel_size_width * game->atlas->sprite_width;
    float psh = game->atlas->pixel_size_height * game->atlas->sprite_height;

    vertex_t *v = malloc(4 * sizeof(vertex_t));
    checkm(v);

    float x_off = x - 0.5f;
    float y_off = y - 0.5f;

    // ll
    v[0].position.x = x_off;
    v[0].position.y = y_off;
    v[0].uv.u = asset->sprite->atlas_offset.x * psw;
    v[0].uv.v = (asset->sprite->atlas_offset.y * psh) + psh;
    // lr
    v[1].position.x = x_off + 1.0f;
    v[1].position.y = y_off;
    v[1].uv.u = (asset->sprite->atlas_offset.x * psw) + psw;
    v[1].uv.v = (asset->sprite->atlas_offset.y * psh) + psh;
    // ur
    v[2].position.x = x_off + 1.0f;
    v[2].position.y = y_off + 1.0f;
    v[2].uv.u = (asset->sprite->atlas_offset.x * psw) + psw;
    v[2].uv.v = asset->sprite->atlas_offset.y * psh;
    // ul
    v[3].position.x = x_off;
    v[3].position.y = y_off + 1.0f;
    v[3].uv.u = asset->sprite->atlas_offset.x * psw;
    v[3].uv.v = asset->sprite->atlas_offset.y * psh;

    memcpy(game->gle->vertex_buffer +
                   (game->gle->vertex_buffer_size * sizeof(float)),
           v, 16 * sizeof(float));
    free(v);

    asset->position.x = x;
    asset->position.y = y;
    asset->visible = true;
    asset->z = 0.0f;

    game->gle->vertex_buffer_size += 16;
    game->gle->element_buffer_size += 6;
    game->assets_count++;
}

void assets_destroy() {
    sprite_type_e sprite_type_total = TOTAL;
    for (int x = 0; x < sprite_type_total; x++) { ffree(game->assets[x]); }
    ffree(game->assets);
}