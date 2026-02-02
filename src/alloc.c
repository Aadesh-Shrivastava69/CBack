#include "alloc.h"

#include <sys/mman.h>
#include <stddef.h>

cback_arena cback_arena_create(u32 size) {
    size = (size + 4095) & ~4095;

    void *mem = mmap(NULL, size, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (mem == MAP_FAILED)
        return (cback_arena){0};

    return (cback_arena){
        .base = mem,
        .size = size,
        .used = 0
    };
}

static inline u32 align_up(u32 size, u32 val) {
    return (size + (val - 1)) & ~(val - 1);
}

void *cback_arena_alloc(cback_arena *a, u32 size) {
    size = align_up(size, 8);

    if (a->used + size > a->size)
        return NULL;

    void *ptr = a->base + a->used;
    a->used += size;
    return ptr;
}

void cback_arena_reset(cback_arena *a) {
    a->used = 0;
}

void cback_arena_destroy(cback_arena *a) {
    munmap(a->base, a->size);
    a->base = NULL;
    a->size = a->used = 0;
}
