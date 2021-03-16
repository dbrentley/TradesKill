//
// Created by dbrent on 3/7/21.
//

#include "assets.h"
#include "game.h"
#include "logger.h"
#include "queue.h"
#include "sprites/effect_bling.h"
#include "sprites/hero.h"
#include "sprites/ore_copper.h"
#include "sprites/ore_gold.h"
#include "utils.h"

#include <stdlib.h>

void assets_init() {
    game->assets = malloc(MAX_SPRITES * sizeof(asset_t *));
    checkm(game->assets);
    for (int x = 0; x < MAX_SPRITES; x++) { asset_init(x); }
}

void asset_init(int n) {
    game->assets[n] = malloc(sizeof(asset_t));
    checkm(game->assets[n]);
    game->assets[n]->index = -1;
    game->assets[n]->one_shot = false;
    game->assets[n]->visible = false;
    game->assets[n]->dirty = false;
    game->assets[n]->scale = 0.5f;
    game->assets[n]->velocity = 1.0f;
    game->assets[n]->z = 0;
    game->assets[n]->animations =
            malloc(ANIMATION_TYPE_TOTAL * sizeof(animation_t *));
    checkm(game->assets[n]->animations);
    game->assets[n]->name = NULL;
    for (int y = 0; y < ANIMATION_TYPE_TOTAL; y++) {
        game->assets[n]->animations[y] = NULL;
    }
}

asset_t *asset_create(sprite_type_e type, const char *name, float x, float y,
                      bool one_shot) {
    int i;
    for (i = 0; i < game->assets_count; i++) {
        if (game->assets[i]->index == -1) { break; }
    }

    switch (type) {
        case HERO:
            hero_init(game->assets[i]);
            break;
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

    if (name != NULL) {
        game->assets[i]->name =
                calloc(strlen(name) + 1, strlen(name) * sizeof(char) + 1);
        checkm(game->assets[i]->name);
        strcpy(game->assets[i]->name, name);
    }

    game->assets[i]->index = i;
    game->assets[i]->visible = true;
    game->assets[i]->one_shot = one_shot;
    game->assets[i]->state = IDLE_S;
    game->assets[i]->position.x = x;
    game->assets[i]->position.y = y;

    vertex_t v[4];

    // ll
    v[0].position.x = game->assets[i]->position.x - game->assets[i]->scale;
    v[0].position.y = game->assets[i]->position.y - game->assets[i]->scale;
    v[0].uv.u = game->assets[i]->animations[IDLE_S]->frames[0];
    v[0].uv.v = game->assets[i]->animations[IDLE_S]->frames[1];
    // lr
    v[1].position.x = game->assets[i]->position.x + game->assets[i]->scale;
    v[1].position.y = game->assets[i]->position.y - game->assets[i]->scale;
    v[1].uv.u = game->assets[i]->animations[IDLE_S]->frames[2];
    v[1].uv.v = game->assets[i]->animations[IDLE_S]->frames[3];
    // ur
    v[2].position.x = game->assets[i]->position.x + game->assets[i]->scale;
    v[2].position.y = game->assets[i]->position.y + game->assets[i]->scale;
    v[2].uv.u = game->assets[i]->animations[IDLE_S]->frames[4];
    v[2].uv.v = game->assets[i]->animations[IDLE_S]->frames[5];
    // ul
    v[3].position.x = game->assets[i]->position.x - game->assets[i]->scale;
    v[3].position.y = game->assets[i]->position.y + game->assets[i]->scale;
    v[3].uv.u = game->assets[i]->animations[IDLE_S]->frames[6];
    v[3].uv.v = game->assets[i]->animations[IDLE_S]->frames[7];

    int offset = i * 16;
    memcpy(game->gle->vertex_buffer + offset, v, 16 * sizeof(float));


    return game->assets[i];
}

void asset_add(sprite_type_e type, char *name, float x, float y,
               bool one_shot) {
    int add_size = queue_size(&game->queues.asset_add);
    int rem_size = queue_size(&game->queues.asset_remove);
    if ((add_size - rem_size) >= MAX_SPRITES) { return; }

    asset_add_queue_entry_t *item = malloc(sizeof(asset_add_queue_entry_t));
    item->type = type;
    item->x = x;
    item->y = y;
    item->one_shot = one_shot;
    item->name = name;
    queue_append(&game->queues.asset_add, item);
}

void asset_remove(asset_t *asset) {
    queue_append(&game->queues.asset_remove, asset);
}

void asset_move(asset_t *asset, asset_facing_e facing) {
    float delta = (float) (asset->velocity * game->timer->delta);
    switch (facing) {
        case N:
            asset->position.y -= delta;
            break;
        case E:
            asset->position.x += delta;
            break;
        case S:
            asset->position.y += delta;
            break;
        case W:
            asset->position.x -= delta;
            break;
        default:
            break;
    }

    int offset = asset->index * 16;
    float v[8];
    // ll
    v[0] = asset->position.x - asset->scale;
    v[1] = asset->position.y - asset->scale;
    // lr
    v[2] = asset->position.x + asset->scale;
    v[3] = asset->position.y - asset->scale;
    // ur
    v[4] = asset->position.x + asset->scale;
    v[5] = asset->position.y + asset->scale;
    // ul
    v[6] = asset->position.x - asset->scale;
    v[7] = asset->position.y + asset->scale;

    int cnt = 0;
    for (int y = 0; y <= 12; y += 4) {
        float m[2];
        m[0] = v[cnt];
        m[1] = v[cnt + 1];
        memcpy(game->gle->vertex_buffer + offset + y, m, 2 * sizeof(float));
        cnt += 2;
    }
}

void asset_animate(asset_t *asset) {
    if (asset->index != -1) {
        float uv[asset->animations[asset->state]->frame_total * 8];
        for (int x = 0; x < asset->animations[asset->state]->frame_total * 8;
             x++) {
            uv[x] = asset->animations[asset->state]->frames[x];
        }

        int cnt = 0;
        int offset = asset->index * 16;
        int current_frame = asset->animations[asset->state]->current_frame;

        for (int p = 2; p < 16; p += 4) {
            float v[2];
            v[0] = uv[cnt + current_frame * 8];
            v[1] = uv[cnt + 1 + current_frame * 8];
            memcpy(game->gle->vertex_buffer + offset + p, v, 2 * sizeof(float));
            cnt += 2;
        }

        asset->animations[asset->state]->current_frame++;
        if (asset->animations[asset->state]->current_frame ==
            asset->animations[asset->state]->frame_total) {
            asset->animations[asset->state]->current_frame = 0;
            if (asset->one_shot) { asset_remove(asset); }
        }
    }
}

void asset_set_active_animation(asset_t *asset, animation_type_e type) {
    asset->state = type;
    asset->animations[type]->current_frame = 0;
}

asset_t *asset_get_by_index(int id) {
    for (int x = 0; x < game->assets_count; x++) {
        if (game->assets[x]->index == id) { return game->assets[x]; }
    }
    return NULL;
}

asset_t *asset_get_by_name(char *name) {
    for (int x = 0; x < game->assets_count; x++) {
        if (strcmp(game->assets[x]->name, name) == 0) {
            return game->assets[x];
        }
    }
    return NULL;
}

void *asset_process_add_queue() {
    while (!game->window->should_close && game->running) {
        for (int x = 0; x < queue_size(&game->queues.asset_add); x++) {
            asset_add_queue_entry_t *item = queue_pop(&game->queues.asset_add);
            if (item != NULL) {
                asset_create(item->type, item->name, item->x, item->y,
                             item->one_shot);
                ffree(item, "asset_process_add_queue");
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

    for (int x = 0; x < SPRITE_TOTAL; x++) {
        animation_destroy(asset->animations[x]);
    }
    asset->name = NULL;
    asset->index = -1;
}

void assets_destroy() {
    for (int x = 0; x < MAX_SPRITES; x++) {
        ffree(game->assets[x], "assets_destroy");
    }
}
