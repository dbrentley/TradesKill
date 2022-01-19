//
// Created by dbrent on 3/6/21.
//

#include "atlas.h"
#include "game.h"
#include "stb_image.h"

#include <stdlib.h>

void atlas_init(char *filename, float sprite_width, float sprite_height) {
    game->atlas = malloc(sizeof(atlas_t));
    if (game->atlas == NULL) {
        printf("Could not allocate memory for atlas\n");
        exit(-1);
    }

    game->atlas->sprite_width = sprite_width;
    game->atlas->sprite_height = sprite_height;

    glGenTextures(1, &game->atlas->texture);
    glBindTexture(GL_TEXTURE_2D, game->atlas->texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    unsigned char *data =
            stbi_load(filename, &game->atlas->width, &game->atlas->height,
                      &game->atlas->channels, STBI_rgb_alpha);
    if (!data) {
        printf("Failed to load atlas texture\n");
        exit(-1);
    }
    printf("Successfully loaded atlas %s\n", filename);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, game->atlas->width,
                 game->atlas->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    game->atlas->pixel_size_width = 1.0f / (float) game->atlas->width;
    game->atlas->pixel_size_height = 1.0f / (float) game->atlas->height;
}

void atlas_destroy() {
    if (game->atlas != NULL) {
        free(game->atlas);
        game->atlas = NULL;
    }
}
