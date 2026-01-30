#include "alloc.h"

#include <sys/mman.h>
#include <stddef.h>

arena_t arena_create(u32 size) {
    size = (size + 4095) & ~4095;

    void *mem = mmap(NULL, size, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (mem == MAP_FAILED) {
        arena_t a = {0};
        return a;
    }

    arena_t a = {
        .base = mem,
        .size = size,
        .used = 0
    };

    return a;
}

static inline u32 align_up(u32 size, u32 val) {
    return (size + (val - 1)) & ~(val - 1);
}

void *arena_alloc(arena_t *a, u32 size) {
    size = align_up(size, 8);

    if (a->used + size > a->size)
        return NULL;

    void *ptr = a->base + a->used;
    a->used += size;
    return ptr;
}

void arena_reset(arena_t *a) {
    a->used = 0;
}

void arena_destroy(arena_t *a) {
    munmap(a->base, a->size);
    a->base = NULL;
    a->size = a->used = 0;
}
