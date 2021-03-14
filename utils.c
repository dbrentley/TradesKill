//
// Created by dbrent on 3/6/21.
//

#include "utils.h"
#include "logger.h"

#include <stdlib.h>

void ffree(void *obj, char *v) {
    if (obj != NULL) {
        free(obj);
        obj = NULL;
    }
}

void checkm(void *obj) {
    if (obj == NULL) {
        logline(ERROR, "Could not allocate memory for object");
        exit(-1);
    }
}

float float_rand(float min, float max) {
    float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + scale * (max - min);        /* [min, max] */
}