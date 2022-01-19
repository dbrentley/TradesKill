//
// Created by dbrent on 3/6/21.
//

#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ffree(void *obj, char *v) {
    if (obj != NULL) {
        free(obj);
        obj = NULL;
    }
}

void checkm(void *obj) {
    if (obj == NULL) {
        printf("Could not allocate memory for object\n");
        exit(-1);
    }
}

float float_rand(float min, float max) {
    float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + scale * (max - min);        /* [min, max] */
}

const char *bytes_to_binary(uint16_t x) {
    static char b[17];
    b[0] = '\0';

    int z;
    for (z = 256; z > 0; z >>= 1) { strcat(b, ((x & z) == z) ? "1" : "0"); }

    return b;
}
