//
// Created by dbrent on 3/7/21.
//

#include "scene_primary.h"
#include "../logger.h"


void scene_primary_init(scene_t *scene) {
    logline(INFO, "Initializing scene %s", scene->name);
}
void scene_primary_update(scene_t *scene) {
}
void scene_primary_render(scene_t *scene) {
    for (int x = 0; x < scene->sprite_size; x++) {
        if (scene->sprites[x] != NULL) {
            //scene->sprites[x]->update(scene->sprites[x]);
            //scene->sprites[x]->render(scene->sprites[x]);
        }
    }
}
