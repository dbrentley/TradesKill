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
    pthread_mutex_lock(&lock);
    int i;
    for (i = 0; i < game->assets_count; i++) {
        if (game->assets[i]->index == -1) { break; }
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

    int offset = i * 16;
    memcpy(game->gle->vertex_buffer + offset, v, 16 * sizeof(float));
    free(v);

    game->assets[i]->position.x = x;
    game->assets[i]->position.y = y;
    game->assets[i]->visible = true;

    //game->assets_count++;
    pthread_mutex_unlock(&lock);
    return game->assets[i];
}

void asset_add(float x, float y, sprite_type_e type) {
    asset_add_queue_entry_t *item = malloc(sizeof(asset_add_queue_entry_t));
    item->type = type;
    item->x = x;
    item->y = y;
    queue_append(&game->queues.asset_add, item);
}

void asset_remove(asset_t *asset) {
    queue_append(&game->queues.asset_remove, asset);
}

asset_t *asset_get_by_index(int id) {
    for (int x = 0; x < game->assets_count; x++) {
        if (game->assets[x]->index == id) { return game->assets[x]; }
    }
    return NULL;
}

void *asset_process_queue() {
    while (!game->window->should_close && game->running) {
        for (int x = 0; x < queue_size(&game->queues.asset_add); x++) {
            asset_add_queue_entry_t *item = queue_pop(&game->queues.asset_add);
            if (item != NULL) {
                asset_create(item->x, item->y, item->type);
                free(item);
            }
        }
        for (int x = 0; x < queue_size(&game->queues.asset_remove); x++) {
            asset_t *item = queue_pop(&game->queues.asset_remove);
            if (item != NULL) { asset_destroy(item); }
        }
    }
    return NULL;
}

void asset_destroy(asset_t *asset) {
    if (asset == NULL || asset->index == -1) { return; }
    pthread_mutex_lock(&lock);
    float v[] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

    int offset = asset->index * 16;
    memcpy(game->gle->vertex_buffer + offset, v, 16 * sizeof(float));

    game->assets[asset->index]->index = -1;
    pthread_mutex_unlock(&lock);
}
