//
// Created by dbrent on 3/6/21.
//

#include "sprite.h"
#include "utils.h"

#include <stdlib.h>

sprite_t *sprite_create(sprite_type_e type) {
    sprite_t *sprite = malloc(sizeof(sprite_t));
    checkm(sprite);

    sprite->type = type;

    return sprite;
}

void sprite_destroy(sprite_t *sprite) { ffree(sprite, "19 sprite.c"); }
