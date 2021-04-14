//
// Created by dbrent on 3/2/21.
//

#ifndef TRADESKILL_GLOBALS_H
#define TRADESKILL_GLOBALS_H

#define DEBUG_ON
#define STB_IMAGE_IMPLEMENTATION

#define DEFAULT_WIDTH 1280
#define DEFAULT_HEIGHT 720
#define MAX_SPRITES 1000000

#define BOUNDS_L -24
#define BOUNDS_R 24
#define BOUNDS_U -14
#define BOUNDS_D 14

#define VERTEX_ELEMENTS 20
#define VERTEX_STRIDE 5

#define OFFSETOF(TYPE, ELEMENT) ((size_t) & (((TYPE *) 0)->ELEMENT))

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "linmath.h"

#endif//TRADESKILL_GLOBALS_H
