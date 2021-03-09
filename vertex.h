//
// Created by dbrent on 3/8/21.
//

#ifndef TRADESKILL_VERTEX_H
#define TRADESKILL_VERTEX_H

typedef struct {
    float position[2];
    float color[3];
    float uv[2];
} vertex_t;

vertex_t *vertex_quad_create(float x, float y);

#endif//TRADESKILL_VERTEX_H
