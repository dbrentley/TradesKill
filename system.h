//
// Created by brent on 1/15/2022.
//

#ifndef TRADESKILL_SYSTEM_H
#define TRADESKILL_SYSTEM_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint8_t n_cores;
    uint8_t n_threads;
    bool hyperthreading;
} cpu_t;

typedef struct {
    cpu_t cpu;
} system_t;

system_t system_init();

#endif//TRADESKILL_SYSTEM_H
