//
// Created by dbrent on 3/4/21.
//

#ifndef TRADESKILL_LOGGER_H
#define TRADESKILL_LOGGER_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

typedef enum {
    DEBUG,
    INFO,
    WARN,
    ERROR
} log_level_e;

static char *get_level(log_level_e level) {
    switch (level) {
        case DEBUG:
            return "DEBUG";
        case INFO:
            return "INFO";
        case WARN:
            return "WARN";
        case ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
}

static void logline(log_level_e level, char *msg, ...) {
    time_t now = time(NULL);
    struct tm *ptm = localtime(&now);
    struct timeval tval_now;
    gettimeofday(&tval_now, NULL);

    char *message = malloc(2048 * sizeof(char));
    strncpy(message, msg, strlen(msg));

    char buf[30];
    strftime(buf, 30, "%d %b %Y %T", ptm);
    sprintf(message, "%s.%06ld", buf, tval_now.tv_usec);
    sprintf(message + (24 * sizeof(char)), " [%s] %s\n", get_level(level), msg);

    va_list args;
    va_start(args, msg);
    vprintf(message, args);
    va_end(args);

    free(message);
}

#endif//TRADESKILL_LOGGER_H
