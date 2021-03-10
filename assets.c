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

void assets_init() {
    game->assets = malloc(MAX_SPRITES * sizeof(asset_t *));
    checkm(game->assets);
    int x;
    for (x = 0; x < MAX_SPRITES; x++) {
        game->assets[x] = malloc(sizeof(asset_t));
        checkm(game->assets[x]);
        game->assets[x]->index = -1;
    }
    logline(INFO, "Initialized %d asset slots", x);
}

void assets_destroy() {
    for (int x = 0; x < MAX_SPRITES; x++) { asset_destroy(game->assets[x]); }
}

asset_t *asset_create(float x, float y, sprite_type_e type) {
    int i, offset = 0;
    int reuse = 0;
    // figure out which slot to put the asset into (memory)
    for (i = 0; i < game->assets_count; i++) {
        if (game->asset_slot[i] == 0) {
            // this asset is taking a previously allocated slot
            if (i < game->assets_count) { reuse = 1; }
            break;
        }
        // TODO: do something when max sprite limit reached
    }

    switch (type) {
        case ORE_GOLD:
            ore_gold_init(game->assets[i]);
            break;
        case ORE_COPPER:
            ore_copper_init(game->assets[i]);
            break;
        default:
            break;
    }


    game->assets[i]->index = i;
    game->asset_slot[i] = 1;

    float psw = game->atlas->pixel_size_width * game->atlas->sprite_width;
    float psh = game->atlas->pixel_size_height * game->atlas->sprite_height;

    vertex_t *v = malloc(4 * sizeof(vertex_t));
    checkm(v);

    float x_off = x - 0.5f;
    float y_off = y - 0.5f;

    // ll
    v[0].position.x = x_off;
    v[0].position.y = y_off;
    v[0].uv.u = game->assets[i]->sprite->atlas_offset.x * psw;
    v[0].uv.v = (game->assets[i]->sprite->atlas_offset.y * psh) + psh;
    // lr
    v[1].position.x = x_off + 1.0f;
    v[1].position.y = y_off;
    v[1].uv.u = (game->assets[i]->sprite->atlas_offset.x * psw) + psw;
    v[1].uv.v = (game->assets[i]->sprite->atlas_offset.y * psh) + psh;
    // ur
    v[2].position.x = x_off + 1.0f;
    v[2].position.y = y_off + 1.0f;
    v[2].uv.u = (game->assets[i]->sprite->atlas_offset.x * psw) + psw;
    v[2].uv.v = game->assets[i]->sprite->atlas_offset.y * psh;
    // ul
    v[3].position.x = x_off;
    v[3].position.y = y_off + 1.0f;
    v[3].uv.u = game->assets[i]->sprite->atlas_offset.x * psw;
    v[3].uv.v = game->assets[i]->sprite->atlas_offset.y * psh;

    offset = game->gle->vertex_buffer_size;

    if (reuse == 1) {
        offset = i * 16;
    } else {
        game->gle->vertex_buffer_size += 16;
        game->gle->element_buffer_size += 6;
    }
    //    logline(INFO, "Creating asset at offset %d with index %d", offset,
    //            game->assets[i]->index);
    memcpy(game->gle->vertex_buffer + offset, v, 16 * sizeof(float));
    free(v);

    game->assets[i]->position.x = x;
    game->assets[i]->position.y = y;
    game->assets[i]->visible = true;

    game->assets_count++;
    return game->assets[i];
}

asset_t *asset_get_by_index(int id) {
    for (int x = 0; x < game->assets_count; x++) {
        if (game->assets[x]->index == id) { return game->assets[x]; }
    }
    return NULL;
}

void asset_destroy(asset_t *asset) {
    if (asset == NULL) { return; }
    // TODO: put this in a queue
    float *v = calloc(4 * sizeof(vertex_t), 4);
    checkm(v);

    int offset = asset->index * 16;
    memcpy(game->gle->vertex_buffer + offset, v, 16 * sizeof(float));
    free(v);

    game->asset_slot[asset->index] = 0;
    game->assets_count--;
    ffree(asset);
}