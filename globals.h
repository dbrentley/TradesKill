//
// Created by dbrent on 3/2/21.
//

#ifndef TRADESKILL_GLOBALS_H
#define TRADESKILL_GLOBALS_H

#define DEBUG_ON
#define GLEW_STATIC

#define DEFAULT_WIDTH 1280
#define DEFAULT_HEIGHT 720
#define MAX_SPRITES 1000000

#define OFFSETOF(TYPE, ELEMENT) ((size_t) & (((TYPE *) 0)->ELEMENT))

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "linmath.h"

#endif//TRADESKILL_GLOBALS_H
