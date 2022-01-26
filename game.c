//
// Created by dbrent on 3/2/21.
//

#include "game.h"
#include "sprites/grass.h"
#include "sprites/ore.h"
#include "utils.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

game_t *game;

#define VIEWPORT_SIZE_X 128
#define VIEWPORT_SIZE_Y 128

void game_init(char *name) {
    game = malloc(sizeof(game_t));
    if (game == NULL) {
        printf("Could not initialize game\n");
        exit(-1);
    }

    game->running = false;
    game->mt = mtwist_new();
    checkm(game->mt);

    queue_init(&game->queues.alloc);
    queue_init(&game->queues.asset_add);
    queue_init(&game->queues.asset_remove);

    window_init(name);
    timer_init();
    state_init();
    atlas_init("assets/atlas.png", 16.0f, 16.0f);

    game->system = system_init();

    game->gle = malloc(sizeof(game_gle_t));
    checkm(game->gle);

    game->gle->vertex_buffer =
            malloc(MAX_SPRITES * sizeof(float) * VERTEX_ELEMENTS);
    checkm(game->gle->vertex_buffer);

    game->gle->element_buffer = malloc(MAX_SPRITES * sizeof(uint32_t) * 6);
    checkm(game->gle->element_buffer);

    game->asset_index = malloc(MAX_SPRITES * sizeof(int));
    checkm(game->asset_index);

    game->asset_array = malloc(MAX_SPRITES * sizeof(float) * VERTEX_ELEMENTS);
    checkm(game->asset_array);

    size_t viewport_size = VIEWPORT_SIZE_X * VIEWPORT_SIZE_Y;
    game->viewport = malloc(viewport_size * sizeof(int));
    checkm(game->viewport);
    for (int x = 0; x < viewport_size; x++) { game->viewport[x] = -1; }

    assets_init();
    game->assets_total = MAX_SPRITES;

    game->viewport_bounds.up = 0;
    game->viewport_bounds.right = 0;
    game->viewport_bounds.left = 0;
    game->viewport_bounds.right = 0;

    game->seed = 0;
    srand(game->seed);

    // vao
    glGenVertexArrays(1, &game->gle->vao);
    glBindVertexArray(game->gle->vao);

    // vbo
    glGenBuffers(1, &game->gle->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, game->gle->vbo);
    glBufferData(GL_ARRAY_BUFFER, MAX_SPRITES * sizeof(float) * VERTEX_ELEMENTS,
                 NULL, GL_DYNAMIC_DRAW);
    // ebo
    int p = 0;
    for (int e = 0; e < MAX_SPRITES - 6; e += 6) {
        game->gle->element_buffer[e] = 0 + p;
        game->gle->element_buffer[e + 1] = 1 + p;
        game->gle->element_buffer[e + 2] = 2 + p;
        game->gle->element_buffer[e + 3] = 2 + p;
        game->gle->element_buffer[e + 4] = 3 + p;
        game->gle->element_buffer[e + 5] = 0 + p;
        p += 4;
    }
    glGenBuffers(1, &game->gle->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, game->gle->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_SPRITES * sizeof(uint32_t),
                 game->gle->element_buffer, GL_STATIC_DRAW);
    // position attribute pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          VERTEX_STRIDE * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    // uv attribute pointer
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
                          VERTEX_STRIDE * sizeof(float),
                          (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    for (int x = 0; x < 348; x++) { game->keys[x] = 0; }

    game->assets_count = 0;
    game->running = true;

    pthread_mutex_init(&lock, NULL);

    //    game->update_z = 0;
    //    pthread_t z_thread_id;
    //    pthread_create(&z_thread_id, NULL, game_asset_sort_z, NULL);
}

void update_viewport() {
    int viewport_width = VIEWPORT_SIZE_X;
    int viewport_height = VIEWPORT_SIZE_Y;
    int viewport_size = viewport_width * viewport_height;

    for (int x = 0; x < viewport_size; x++) {
        /**
         * TODO: Handle sprites larger than 16x16
         */
        if (game->viewport[x] == -1) {
            int x_pos = x % viewport_width;
            int y_pos = (int) floor((double) x / viewport_width);

            asset_t *ore = asset_create(ore_init, NULL, (float) x_pos,
                                        (float) y_pos, NONE, false);
            ore->visible = true;


            asset_t *grass = asset_create(grass_init, NULL, (float) x_pos,
                                          (float) y_pos, NONE, false);
            grass->visible = true;


            game->viewport[x] = 1;
        }
    }
}

void game_update() {
    update_viewport();
    // game->update_z = 1;
    for (int x = 0; x < game->assets_count; x++) {
        if (game->assets[x]->index != -1) {
            game->assets[x]->update(game->assets[x]);
        }
    }
}

void *game_asset_sort_z() {
    while (game != NULL) {
        if (game->update_z == 1) {
            int asset_index[game->assets_count][2];
            int asset_index_cnt = 0;
            for (int x = 0; x < game->assets_count; x++) {
                if (game->assets[x]->index != -1) {
                    asset_index[asset_index_cnt][0] = game->assets[x]->index;
                    asset_index[asset_index_cnt][1] =
                            game->assets[x]->grid_height * 16;
                    asset_index_cnt++;
                }
            }
            // bubble sort - inefficient - replace with selection or quick
            bool sorted = false;
            bool did_sort = false;
            while (sorted == false) {
                for (int i = 0; i < game->assets_count - 1; i++) {
                    if (asset_index[i][1] > asset_index[i + 1][1]) {
                        int t0 = asset_index[i][0];
                        int t1 = asset_index[i][1];
                        asset_index[i][0] = asset_index[i + 1][0];
                        asset_index[i][1] = asset_index[i + 1][1];
                        asset_index[i + 1][0] = t0;
                        asset_index[i + 1][1] = t1;
                        did_sort = true;
                    }
                }
                if (did_sort == true) {
                    sorted = false;
                    did_sort = false;
                } else {
                    sorted = true;
                }
            }
            for (int i = 0; i < game->assets_count; i++) {
                int offset = asset_index[i][0] * VERTEX_ELEMENTS;
                memcpy(game->gle->vertex_buffer + (i * VERTEX_ELEMENTS),
                       game->asset_array + offset,
                       VERTEX_ELEMENTS * sizeof(float));
            }
            game->update_z = 0;
        }
    }
}

void game_destroy() {
    state_destroy();
    timer_destroy();
    window_destroy();
    assets_destroy();
    atlas_destroy();

    ffree(game->gle, "gle game_destroy");
    ffree(game->asset_array, "asset_array game_destroy");
    ffree(game, "game_destroy");
}
