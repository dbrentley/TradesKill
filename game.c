//
// Created by dbrent on 3/2/21.
//

#include "game.h"
#include "logger.h"
#include "scene.h"
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
    checkm(game->scenes, "game scenes");
    game->scene_count = 0;
    game->scene_size = 0;

    window_init(name);
    timer_init();
    state_init();
    atlas_init("assets/sprites/atlas.png", 16.0f, 16.0f);

    scene_t *main_scene = scene_create("main_scene");
    game->current_scene = main_scene;
    game_scene_add(main_scene);
}

void game_scene_add(scene_t *scene) {
    if (game->scene_count == game->scene_size) {
        game->scenes = realloc(game->scenes, game->scene_count + 1 * sizeof(scene_t *));
        checkm(game->scenes, "scenes realloc");
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

void game_scene_remove(scene_t *scene) {
}

void game_destroy() {
    state_destroy();
    timer_destroy();
    window_destroy();
    atlas_destroy();

    for (int x = 0; x < game->scene_size; x++) {
        scene_destroy(game->scenes[x]);
    }
    ffree(game->scenes);
    ffree(game);
}
