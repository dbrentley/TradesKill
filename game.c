//
// Created by dbrent on 3/2/21.
//

#include "game.h"
#include "assets.h"
#include "logger.h"
#include "utils.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

game_t *game;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void game_init(char *name) {
    game = malloc(sizeof(game_t));
    if (game == NULL) {
        logline(ERROR, "Could not initialize game");
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

    game->gle = malloc(sizeof(game_gle_t));
    checkm(game->gle);

    game->gle->vertex_buffer = malloc(MAX_SPRITES * sizeof(float) * 16);
    checkm(game->gle->vertex_buffer);

    game->gle->element_buffer = malloc(MAX_SPRITES * sizeof(uint32_t) * 6);
    checkm(game->gle->element_buffer);

    assets_init();
    game->assets_count = MAX_SPRITES;

    // vao
    glGenVertexArrays(1, &game->gle->vao);
    glBindVertexArray(game->gle->vao);

    // vbo
    glGenBuffers(1, &game->gle->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, game->gle->vbo);
    glBufferData(GL_ARRAY_BUFFER, MAX_SPRITES * sizeof(float) * 16, NULL,
                 GL_DYNAMIC_DRAW);
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
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    // uv attribute pointer
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                          (void *) (2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    game->running = true;
}

void game_render() {
    glBindTexture(GL_TEXTURE_2D, game->atlas->texture);
    glBindVertexArray(game->gle->vao);
    glBindBuffer(GL_ARRAY_BUFFER, game->gle->vbo);

    for (int x = 0; x < game->assets_count; x++) {
        if (game->assets[x]->index != -1) {
            game->assets[x]->update(game->assets[x]);
            if (game->assets[x]->visible) {
                game->assets[x]->render(game->assets[x]);
            }
        }
    }

    glBufferSubData(GL_ARRAY_BUFFER, 0, MAX_SPRITES * sizeof(float) * 16,
                    game->gle->vertex_buffer);

    glDrawElements(GL_TRIANGLES, MAX_SPRITES, GL_UNSIGNED_INT, 0);
}


void game_destroy() {
    state_destroy();
    timer_destroy();
    window_destroy();
    assets_destroy();
    atlas_destroy();

    //    queue_destroy(&game->queues.alloc);
    //    queue_destroy(&game->queues.asset_add);
    //    queue_destroy(&game->queues.asset_remove);

    ffree(game->gle);
    ffree(game);
}
