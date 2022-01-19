//
// Created by dbrent on 3/2/21.
//

#ifndef TRADESKILL_TIMER_H
#define TRADESKILL_TIMER_H

typedef struct {
    double time;
    double previous_time;
    double start_time;
    double end_time;
    double delta;
    int frame_count;
    int fps;
} game_timer_t;

void timer_init();

void timer_start();

void timer_end();

void timer_destroy();

#endif//TRADESKILL_TIMER_H
