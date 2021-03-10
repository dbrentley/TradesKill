//
// Created by dbrent on 3/2/21.
//

#ifndef TRADESKILL_GLOBALS_H
#define TRADESKILL_GLOBALS_H

#define DEBUG_ON
#define GLEW_STATIC

#define DEFAULT_WIDTH 1920
#define DEFAULT_HEIGHT 1080
#define MAX_SPRITES 75000

#define OFFSETOF(TYPE, ELEMENT) ((size_t) & (((TYPE *) 0)->ELEMENT))

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "linmath.h"

#endif//TRADESKILL_GLOBALS_H
