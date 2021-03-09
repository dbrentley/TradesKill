//
// Created by dbrent on 3/6/21.
//

#ifndef TRADESKILL_ATLAS_H
#define TRADESKILL_ATLAS_H

#include "globals.h"

typedef struct {
    float x;
    float y;
} atlas_position_t;

typedef struct {
    char *filename;
    int width;
    int height;
    int channels;
    float pixel_size_width;
    float pixel_size_height;
    float sprite_width;
    float sprite_height;
    GLuint texture;
} atlas_t;

void atlas_init(char *filename, float sprite_width, float sprite_height);

void atlas_destroy();

#endif//TRADESKILL_ATLAS_H
