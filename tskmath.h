//
// Created by brent on 1/18/2022.
//

#ifndef TRADESKILL_TSKMATH_H
#define TRADESKILL_TSKMATH_H


typedef struct POINT {
    double x, y;
} point_2d_t;

typedef struct VECTOR {
    point_2d_t p, q;
} vector_2d_t;

// https://stackoverflow.com/questions/19564229/how-to-get-the-vector-direction-between-two-p1-p2
static double get_vector_2d_direction(vector_2d_t v) {
    return atan2(v.q.y - v.p.y, v.q.x - v.p.x); /* atan(ratio) */
}

static double get_vector_2d_distance(vector_2d_t v) {
    return sqrt(pow(v.q.x - v.p.x, 2) + pow(v.q.y - v.p.y, 2));
}

static double to_degrees(double radians) { return radians * (180.0 / M_PI); }

#endif//TRADESKILL_TSKMATH_H
