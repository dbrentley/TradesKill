//
// Created by dbrent on 3/2/21.
//

#include "game.h"
#include "assets.h"
#include "logger.h"
#include "scene.h"
#include "scenes/scene_primary.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

game_t *game;

void game_init(char *name) {
    game = malloc(sizeof(game_t));
    if (game == NULL) {
        logline(ERROR, "Could not initialize game");
        exit(-1);
    }

    game->scenes = malloc(sizeof(scene_t *));
    checkm(game->scenes);
    game->scene_count = 0;
    game->scene_size = 0;

    window_init(name);

    timer_init();
    state_init();
    atlas_init("assets/atlas.png", 16.0f, 16.0f);

    game->gle = malloc(sizeof(game_gle_t));
    checkm(game->gle);

    game->gle->vertex_buffer = malloc(MAX_SPRITES * sizeof(float));
    checkm(game->gle->vertex_buffer);
    game->gle->vertex_buffer_size = 0;

    game->gle->element_buffer = malloc(MAX_SPRITES * sizeof(uint32_t));
    checkm(game->gle->element_buffer);
    game->gle->element_buffer_size = 0;

    assets_init();
    game->assets_count = 0;

    // vao
    glGenVertexArrays(1, &game->gle->vao);
    glBindVertexArray(game->gle->vao);

    // vbo
    glGenBuffers(1, &game->gle->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, game->gle->vbo);
    glBufferData(GL_ARRAY_BUFFER, MAX_SPRITES * sizeof(float), NULL,
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

    scene_t *main_scene =
            scene_create("scene_primary", scene_primary_init,
                         scene_primary_update, scene_primary_render);
    game->current_scene = main_scene;
    game_scene_add(main_scene);

    asset_create(0.0f, 0.0f, game->assets[ORE_GOLD]);
    asset_create(1.0f, 0.0f, game->assets[ORE_COPPER]);
}

void game_render() {
    for (int x = 0; x < game->scene_size; x++) {
        game->current_scene->update(game->current_scene);
        game->current_scene->render(game->current_scene);
    }
    for (int x = 0; x < game->assets_count; x++) {
        game->assets[x]->update(game->assets[x]);
    }
    glBindTexture(GL_TEXTURE_2D, game->atlas->texture);
    glBindVertexArray(game->gle->vao);
    glBindBuffer(GL_ARRAY_BUFFER, game->gle->vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0,
                    game->gle->vertex_buffer_size * sizeof(float),
                    game->gle->vertex_buffer);

    glDrawElements(GL_TRIANGLES, game->gle->element_buffer_size,
                   GL_UNSIGNED_INT, 0);
}

void game_scene_add(scene_t *scene) {
    if (game->scene_count == game->scene_size) {
        game->scenes = realloc(game->scenes,
                               game->scene_count + 1 * sizeof(scene_t *));
        checkm(game->scenes);
        game->scene_size++;
        game->scenes[game->scene_size] = NULL;
    }
    for (int x = 0; x < game->scene_size; x++) {
        if (game->scenes[x] == NULL) {
            game->scenes[x] = malloc(sizeof(scene_t));
            memcpy(game->scenes[x], scene, sizeof(*scene));
            break;
        }
    }
}

void game_scene_remove(scene_t *scene) {}

void game_destroy() {
    state_destroy();
    timer_destroy();
    window_destroy();
    assets_destroy();
    atlas_destroy();

    for (int x = 0; x < game->scene_size; x++) {
        scene_destroy(game->scenes[x]);
    }
    ffree(game->scenes);
    ffree(game->gle->vertex_buffer);
    ffree(game->gle->element_buffer);
    ffree(game->gle);
    ffree(game);
}
