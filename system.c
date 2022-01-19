//
// Created by brent on 1/15/2022.
//

#include "system.h"

system_t system_init() {
    unsigned int ncores = 0, nthreads = 0, ht;
    asm volatile("cpuid" : "=a"(ncores), "=b"(nthreads) : "a"(0xb), "c"(0x1) :);
    ht = (ncores != nthreads);

    system_t system = {.cpu.hyperthreading = ht,
                       .cpu.n_cores = ncores,
                       .cpu.n_threads = nthreads};
    return system;
};
