//
// Created by dbrent on 3/6/21.
//

#include "utils.h"
#include "logger.h"

#include <stdlib.h>

void ffree(void *obj) {
    if (obj != NULL) {
        free(obj);
        obj = NULL;
    }
}

void checkm(void *obj, char *name) {
    if (obj == NULL) {
        logline(ERROR, "Could not allocate memory for %s", name);
        exit(-1);
    }
}