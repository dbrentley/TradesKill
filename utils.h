//
// Created by dbrent on 3/6/21.
//

#ifndef TRADESKILL_UTILS_H
#define TRADESKILL_UTILS_H

#include <stdint.h>

void ffree(void *obj, char *v);

void checkm(void *obj);

float float_rand(float min, float max);

const char *bytes_to_binary(uint16_t x);

#endif//TRADESKILL_UTILS_H
