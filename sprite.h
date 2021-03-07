//
// Created by dbrent on 3/6/21.
//

#ifndef TRADESKILL_SPRITE_H
#define TRADESKILL_SPRITE_H

typedef struct sprite_t sprite_t;

typedef void (*update_m)(sprite_t *);
typedef void (*render_m)(sprite_t *);

typedef enum {
    WALK,
    RUN,
    IDLE,
    ATTACK,
    DODGE,
    DEATH
} animation_type_e;

typedef struct {
    animation_type_e anim_type;
    int frames;
} animation_t;

typedef struct {
    float size_w;
    float size_h;
} sprite_texture_t;

typedef struct {
    float z;
    float x;
    float y;
    float rotation;
    float zoom;
} sprite_position_t;

typedef struct {
    float x;
    float y;
} atlas_offset_t;

struct sprite_t {
    char *name;
    atlas_offset_t atlas_offset;
    sprite_position_t position;
    sprite_texture_t texture;
    animation_t **animations;
    render_m render;
    update_m update;
};

sprite_t *sprite_create(char *name, atlas_offset_t atlas_offset);

void sprite_destroy(sprite_t *sprite);

void sprite_update(sprite_t *);

void sprite_render(sprite_t *);

#endif//TRADESKILL_SPRITE_H
