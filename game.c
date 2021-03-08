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
    atlas_init("assets/red-potion.png", 16.0f, 16.0f);

    int total_assets = assets_init();
    game->gle = malloc(sizeof(game_gle_t));
    checkm(game->gle);

    int vertex_attributes = 4;

    game->gle->vertex_buffer = malloc(total_assets * sizeof(float) * 32);
    checkm(game->gle->vertex_buffer);
    game->gle->vertex_buffer_size = 32;
    float vb[] = {
            // position   uv
            -1.5f, -0.5f, 0.0f, 1.0f,// ll 0
            -0.5f, -0.5f, 1.0f, 1.0f,// lr 1
            -0.5f, 0.5f,  1.0f, 0.0f,// ur 2
            -1.5f, 0.5f,  0.0f, 0.0f,// ul 3

            5.0f,  -0.5f, 0.0f, 1.0f,// ll 4
            6.0f,  -0.5f, 1.0f, 1.0f,// lr 5
            6.0f,  0.5f,  1.0f, 0.0f,// ur 6
            5.0f,  0.5f,  0.0f, 0.0f,// ul 7
    };
    memcpy(game->gle->vertex_buffer, vb, 32 * sizeof(float));

    game->gle->element_buffer = malloc(total_assets * sizeof(uint32_t) * 12);
    checkm(game->gle->element_buffer);
    game->gle->element_buffer_size = 12;
    uint32_t eb[] = {
            1, 0, 2, 2, 0, 3,// 1
            5, 4, 6, 6, 7, 4 //2
    };
    memcpy(game->gle->element_buffer, eb, 12 * sizeof(uint32_t));

    // vao
    glGenVertexArrays(1, &game->gle->vao);
    glBindVertexArray(game->gle->vao);
    // vbo
    glGenBuffers(1, &game->gle->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, game->gle->vbo);
    glBufferData(GL_ARRAY_BUFFER, game->gle->vertex_buffer_size * sizeof(float),
                 game->gle->vertex_buffer, GL_DYNAMIC_DRAW);
    // ebo
    glGenBuffers(1, &game->gle->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, game->gle->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 game->gle->element_buffer_size * sizeof(uint32_t),
                 game->gle->element_buffer, GL_STATIC_DRAW);
    // position attribute pointer
    int position_size = 2;
    glVertexAttribPointer(0, position_size, GL_FLOAT, GL_FALSE,
                          vertex_attributes * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    // uv attribute pointer
    int uv_size = 2;
    glVertexAttribPointer(1, uv_size, GL_FLOAT, GL_FALSE,
                          vertex_attributes * sizeof(float),
                          (void *) (position_size * sizeof(float)));
    glEnableVertexAttribArray(1);

    scene_t *main_scene =
            scene_create("scene_primary", scene_primary_init,
                         scene_primary_update, scene_primary_render);
    game->current_scene = main_scene;
    game_scene_add(main_scene);
}

void game_render() {
    for (int x = 0; x < game->scene_size; x++) {
        game->current_scene->update(game->current_scene);
        game->current_scene->render(game->current_scene);
    }
    glBindTexture(GL_TEXTURE_2D, game->atlas->texture);
    glBindVertexArray(game->gle->vao);

    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
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
