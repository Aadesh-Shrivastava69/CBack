#ifndef ALLOC_H
#define ALLOC_H

#include "utils.h"

typedef struct {
    u8 *base;
    u32 size;
    u32 used;
} arena_t;

arena_t arena_create(u32 size);
void arena_destroy(arena_t *a);
void *arena_alloc(arena_t *a, u32 size);
void arena_reset(arena_t *a);

#endif
