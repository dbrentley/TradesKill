//
// Created by dbrent on 3/7/21.
//

#include "assets.h"
#include "game.h"
#include "queue.h"
#include "sprites/effect_bling.h"
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
        game->assets[x]->one_shot = false;
        game->assets[x]->visible = false;
        game->assets[x]->z = 0;
        game->assets[x]->animations = malloc(TOTAL * sizeof(animation_t *));
        checkm(game->assets[x]->animations);
    }
}

asset_t *asset_create(sprite_type_e type) {
    int i;
    for (i = 0; i < game->assets_count; i++) {
        if (game->assets[i]->index == -1) { break; }
    }

    switch (type) {
        case ORE_GOLD:
            ore_gold_init(game->assets[i]);
            break;
        case ORE_COPPER:
            ore_copper_init(game->assets[i]);
            break;
        case EFFECT_BLING:
            effect_bling_init(game->assets[i]);
            break;
        default:
            break;
    }

    game->assets[i]->index = i;
    game->assets[i]->visible = true;
    game->assets[i]->state = IDLE;
    game->assets[i]->position.x = 0;
    game->assets[i]->position.y = 0;

    float pos_x, pos_y = 0;
    vertex_t v[4];

    // ll
    v[0].position.x = pos_x;
    v[0].position.y = pos_y;
    v[0].uv.u = game->assets[i]->animations[IDLE]->frames[0];
    v[0].uv.v = game->assets[i]->animations[IDLE]->frames[1];
    // lr
    v[1].position.x = pos_x + 1.0f;
    v[1].position.y = pos_y;
    v[1].uv.u = game->assets[i]->animations[IDLE]->frames[2];
    v[1].uv.v = game->assets[i]->animations[IDLE]->frames[3];
    // ur
    v[2].position.x = pos_x + 1.0f;
    v[2].position.y = pos_y + 1.0f;
    v[2].uv.u = game->assets[i]->animations[IDLE]->frames[4];
    v[2].uv.v = game->assets[i]->animations[IDLE]->frames[5];
    // ul
    v[3].position.x = pos_x;
    v[3].position.y = pos_y + 1.0f;
    v[3].uv.u = game->assets[i]->animations[IDLE]->frames[6];
    v[3].uv.v = game->assets[i]->animations[IDLE]->frames[7];

    int offset = i * 16;
    memcpy(game->gle->vertex_buffer + offset, v, 16 * sizeof(float));


    return game->assets[i];
}

void asset_add(sprite_type_e type) {
    asset_add_queue_entry_t *item = malloc(sizeof(asset_add_queue_entry_t));
    item->type = type;
    queue_append(&game->queues.asset_add, item);
}

void asset_remove(asset_t *asset) {
    queue_append(&game->queues.asset_remove, asset);
}

void asset_animation_add(asset_t *asset, animation_t *animation) {
    animation_t *anim = malloc(sizeof(animation_t));
    checkm(anim);
}

void asset_animate(asset_t *asset) {
    if (asset->index != -1 &&
        asset->animations[asset->state]->frame_total > 1) {

        float uv[asset->animations[asset->state]->frame_total * 8];
        for (int x = 0; x < asset->animations[asset->state]->frame_total * 8;
             x++) {
            uv[x] = asset->animations[asset->state]->frames[x];
        }

        vertex_t v[4];
        int current_frame = asset->animations[asset->state]->current_frame;
        // ll
        v[0].position.x = asset->position.x;
        v[0].position.y = asset->position.y;
        v[0].uv.u = uv[0 + current_frame * 8];
        v[0].uv.v = uv[1 + current_frame * 8];
        // lr
        v[1].position.x = asset->position.x + 1.0f;
        v[1].position.y = 0;
        v[1].uv.u = uv[2 + current_frame * 8];
        v[1].uv.v = uv[3 + current_frame * 8];
        // ur
        v[2].position.x = asset->position.x + 1.0f;
        v[2].position.y = asset->position.y + 1.0f;
        v[2].uv.u = uv[4 + current_frame * 8];
        v[2].uv.v = uv[5 + current_frame * 8];
        // ul
        v[3].position.x = asset->position.x;
        v[3].position.y = asset->position.y + 1.0f;
        v[3].uv.u = uv[6 + current_frame * 8];
        v[3].uv.v = uv[7 + current_frame * 8];

        int offset = asset->index * 16;
        memcpy(game->gle->vertex_buffer + offset, v, 16 * sizeof(float));

        if (asset->animations[asset->state]->time.end_time -
                    asset->animations[asset->state]->time.start_time >
            1.0 - asset->animations[asset->state]->speed) {

            asset->animations[asset->state]->current_frame++;
            if (asset->animations[asset->state]->current_frame ==
                asset->animations[asset->state]->frame_total) {
                asset->animations[asset->state]->current_frame = 0;
                if (asset->one_shot) { asset_remove(asset); }
            }

            asset->animations[asset->state]->time.start_time =
                    asset->animations[asset->state]->time.end_time;
        }
        asset->animations[asset->state]->time.end_time = glfwGetTime();
    }
}

void asset_set_active_animation(asset_t *asset, animation_type_e type) {
    asset->state = type;
}

asset_t *asset_get_by_index(int id) {
    for (int x = 0; x < game->assets_count; x++) {
        if (game->assets[x]->index == id) { return game->assets[x]; }
    }
    return NULL;
}

void *asset_process_add_queue() {
    while (!game->window->should_close && game->running) {
        for (int x = 0; x < queue_size(&game->queues.asset_add); x++) {
            asset_add_queue_entry_t *item = queue_pop(&game->queues.asset_add);
            if (item != NULL) {
                asset_create(item->type);
                free(item);
            }
        }
    }
    return NULL;
}

void *asset_process_rem_queue() {
    while (!game->window->should_close && game->running) {
        for (int x = 0; x < queue_size(&game->queues.asset_remove); x++) {
            asset_t *item = queue_pop(&game->queues.asset_remove);
            if (item != NULL) { asset_destroy(item); }
        }
    }
    return NULL;
}

void asset_destroy(asset_t *asset) {
    if (asset == NULL || asset->index == -1) { return; }
    float v[] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

    int offset = asset->index * 16;
    memcpy(game->gle->vertex_buffer + offset, v, 16 * sizeof(float));

    game->assets[asset->index]->index = -1;
    game->assets[asset->index]->visible = false;
}

void assets_destroy() {
    for (int x = 0; x < MAX_SPRITES; x++) { ffree(game->assets[x]); }
}
