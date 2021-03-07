//
// Created by dbrent on 3/6/21.
//

#include "sprite.h"
#include "logger.h"
#include "utils.h"

#include <stdlib.h>
#include <string.h>

sprite_t *sprite_create(char *name, atlas_offset_t atlas_offset) {
    sprite_t *sprite = malloc(sizeof(sprite_t));
    checkm(sprite, name);
    sprite->atlas_offset = atlas_offset;

    sprite->name = calloc(strlen(name) * sizeof(char) + 1, strlen(name) + 1);
    strncpy(sprite->name, name, strlen(name));

    sprite->update = sprite_update;
    sprite->render = sprite_render;

    return sprite;
}

void sprite_update(sprite_t *sprite) {
    logline(INFO, "sprite update");
}

void sprite_render(sprite_t *sprite) {
    logline(INFO, "sprite render");
}

void sprite_destroy(sprite_t *sprite) {
    ffree(sprite->name);
    ffree(sprite);
}