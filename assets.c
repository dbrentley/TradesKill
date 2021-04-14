//
// Created by dbrent on 3/7/21.
//

#include "assets.h"
#include "game.h"
#include "sprites/effect_bling.h"
#include "sprites/grass.h"
#include "sprites/hero.h"
#include "sprites/ore_copper.h"
#include "sprites/ore_gold.h"
#include "utils.h"

#include <stdio.h>
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
    game->assets[n]->speed = 1.0f;
    game->assets[n]->animations =
            malloc(ANIMATION_TYPE_TOTAL * sizeof(animation_t *));
    checkm(game->assets[n]->animations);
    game->assets[n]->name = NULL;
    for (int y = 0; y < ANIMATION_TYPE_TOTAL; y++) {
        game->assets[n]->animations[y] = NULL;
    }
}

asset_t *asset_create(sprite_type_e type, const char *name, float x, float y,
                      animation_type_e default_animation, bool one_shot) {
    int i;
    for (i = 0; i < game->assets_total; i++) {
        if (game->assets[i]->index == -1) { break; }
    }

    switch (type) {
        case HERO:
            hero_init(game->assets[i]);
            break;
        case GRASS:
            grass_init(game->assets[i]);
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
        strncpy(game->assets[i]->name, name, strlen(name));
    }

    game->assets[i]->index = i;
    game->assets[i]->z_index = 0;
    game->assets[i]->one_shot = one_shot;
    game->assets[i]->position.x = x;
    game->assets[i]->position.y = y;
    game->assets[i]->position.z = 1;
    game->assets[i]->col_height = (float) game->assets[i]->sprite->size.height;
    game->assets[i]->state = default_animation;
    game->assets[i]->animations[NONE] =
            animation_create(NONE, game->assets[i]->sprite, 1,
                             game->assets[i]->sprite->atlas_offset.x,
                             game->assets[i]->sprite->atlas_offset.y, 0);

    vertex_t v[4];

    // ll
    v[0].position.x = game->assets[i]->position.x - game->assets[i]->scale;
    v[0].position.y = game->assets[i]->position.y - game->assets[i]->scale;
    v[0].position.z = game->assets[i]->position.z;
    v[0].uv.u = game->assets[i]->animations[game->assets[i]->state]->frames[0];
    v[0].uv.v = game->assets[i]->animations[game->assets[i]->state]->frames[1];
    // lr
    v[1].position.x = game->assets[i]->position.x + game->assets[i]->scale;
    v[1].position.y = game->assets[i]->position.y - game->assets[i]->scale;
    v[1].position.z = game->assets[i]->position.z;
    v[1].uv.u = game->assets[i]->animations[game->assets[i]->state]->frames[2];
    v[1].uv.v = game->assets[i]->animations[game->assets[i]->state]->frames[3];
    // ur
    v[2].position.x = game->assets[i]->position.x + game->assets[i]->scale;
    v[2].position.y = game->assets[i]->position.y + game->assets[i]->scale;
    v[2].position.z = game->assets[i]->position.z;
    v[2].uv.u = game->assets[i]->animations[game->assets[i]->state]->frames[4];
    v[2].uv.v = game->assets[i]->animations[game->assets[i]->state]->frames[5];
    // ul
    v[3].position.x = game->assets[i]->position.x - game->assets[i]->scale;
    v[3].position.y = game->assets[i]->position.y + game->assets[i]->scale;
    v[3].position.z = game->assets[i]->position.z;
    v[3].uv.u = game->assets[i]->animations[game->assets[i]->state]->frames[6];
    v[3].uv.v = game->assets[i]->animations[game->assets[i]->state]->frames[7];

    int offset = i * VERTEX_ELEMENTS;
    //    memcpy(game->gle->vertex_buffer + offset, v,
    //           VERTEX_ELEMENTS * sizeof(float));
    memcpy(game->asset_array + offset, v, VERTEX_ELEMENTS * sizeof(float));

    game->assets_count++;
    return game->assets[i];
}

void asset_move(asset_t *asset, asset_facing_e facing) {
    float delta = (float) (asset->speed * game->timer->delta);

    if ((game->keys[GLFW_KEY_A] && game->keys[GLFW_KEY_W]) ||
        (game->keys[GLFW_KEY_W] && game->keys[GLFW_KEY_D]) ||
        (game->keys[GLFW_KEY_S] && game->keys[GLFW_KEY_D]) ||
        (game->keys[GLFW_KEY_A] && game->keys[GLFW_KEY_S])) {
        delta /= 1.5f;
    }

    switch (facing) {
        case N:
            asset->position.y += delta;
            break;
        case S:
            asset->position.y -= delta;
            break;
        case E:
            asset->position.x += delta;
            break;
        case W:
            asset->position.x -= delta;
            break;
        default:
            break;
    }

    int offset = asset->index * VERTEX_ELEMENTS;
    float v[12];

    // ll
    v[0] = asset->position.x - asset->scale;
    v[1] = asset->position.y - asset->scale;
    v[2] = asset->position.z;
    // lr
    v[3] = asset->position.x + asset->scale;
    v[4] = asset->position.y - asset->scale;
    v[5] = asset->position.z;
    // ur
    v[6] = asset->position.x + asset->scale;
    v[7] = asset->position.y + asset->scale;
    v[8] = asset->position.z;
    // ul
    v[9] = asset->position.x - asset->scale;
    v[10] = asset->position.y + asset->scale;
    v[11] = asset->position.z;

    int cnt = 0;
    int position_size = 3;// x, y, z
    for (int y = 0; y < VERTEX_ELEMENTS; y += VERTEX_STRIDE) {
        float m[position_size];
        for (int x = 0; x < position_size; x++) { m[x] = v[cnt + x]; }
        //        memcpy(game->gle->vertex_buffer + offset + y, m,
        //               position_size * sizeof(float));
        memcpy(game->asset_array + offset + y, m,
               position_size * sizeof(float));
        cnt += 3;
    }
}

void asset_animate(asset_t *asset) {
    if (asset->index != -1) {
        // 8 = 2 uv * 4 vertex
        float uv[asset->animations[asset->state]->frame_total * 8];
        for (int x = 0; x < asset->animations[asset->state]->frame_total * 8;
             x++) {
            uv[x] = asset->animations[asset->state]->frames[x];
        }

        int cnt = 0;
        int offset = asset->index * VERTEX_ELEMENTS;
        int current_frame = asset->animations[asset->state]->current_frame;
        int uv_size = 2;

        for (int p = 3; p < VERTEX_ELEMENTS; p += VERTEX_STRIDE) {
            float v[2];
            v[0] = uv[cnt + current_frame * 8];
            v[1] = uv[cnt + 1 + current_frame * 8];
            //            memcpy(game->gle->vertex_buffer + offset + p, v,
            //                   uv_size * sizeof(float));
            memcpy(game->asset_array + offset + p, v, uv_size * sizeof(float));
            cnt += 2;
        }

        asset->animations[asset->state]->current_frame++;
        if (asset->animations[asset->state]->current_frame ==
            asset->animations[asset->state]->frame_total) {
            asset->animations[asset->state]->current_frame = 0;
            if (asset->one_shot) { asset_destroy(asset); }
        }
    }
}

void asset_set_active_animation(asset_t *asset, animation_type_e type) {
    asset->state = type;
}

asset_t *asset_get_by_index(int id) {
    for (int x = 0; x < game->assets_total; x++) {
        if (game->assets[x]->index == id) { return game->assets[x]; }
    }
    return NULL;
}

asset_t *asset_get_by_name(char *name) {
    for (int x = 0; x < game->assets_total; x++) {
        if (strcmp(game->assets[x]->name, name) == 0) {
            return game->assets[x];
        }
    }
    return NULL;
}

void asset_destroy(asset_t *asset) {
    if (asset == NULL || asset->index == -1) { return; }
    game->assets_count--;
    float v[] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

    int offset = asset->index * VERTEX_ELEMENTS;
    //    memcpy(game->gle->vertex_buffer + offset, v,
    //           VERTEX_ELEMENTS * sizeof(float));
    memcpy(game->asset_array + offset, v, VERTEX_ELEMENTS * sizeof(float));

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
