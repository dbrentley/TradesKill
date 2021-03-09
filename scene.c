//
// Created by dbrent on 3/6/21.
//

#include "scene.h"
#include "utils.h"

#include <stdlib.h>
#include <string.h>

scene_t *scene_create(char *name, scene_init_f init, scene_update_f update,
                      scene_render_f render) {
    scene_t *scene = malloc(sizeof(scene_t));
    checkm(scene);

    scene->name = malloc(strlen(name) * sizeof(char) + 1);
    checkm(scene->name);
    strncpy(scene->name, name, strlen(name));

    scene->sprites = malloc(10 * sizeof(sprite_t *));
    checkm(scene->sprites);
    scene->sprite_count = 0;
    scene->sprite_size = 0;

    scene->init = init;
    scene->update = update;
    scene->render = render;

    scene->init(scene);

    return scene;
}

void scene_sprite_add(scene_t *scene, sprite_t *sprite) {
}

void scene_destroy(scene_t *scene) {
    ffree(scene->name);
    for (int x = 0; x < scene->sprite_size; x++) {
        sprite_destroy(scene->sprites[x]);
    }
    ffree(scene->sprites);
    ffree(scene);
}