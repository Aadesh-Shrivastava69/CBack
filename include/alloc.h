#ifndef ALLOC_H
#define ALLOC_H

#include "utils.h"

typedef struct {
    u8 *base;
    u32 size;
    u32 used;
} cback_arena;

cback_arena cback_arena_create(u32 size);
void cback_arena_destroy(cback_arena *a);
void *cback_arena_alloc(cback_arena *a, u32 size);
void cback_arena_reset(cback_arena *a);

#endif
