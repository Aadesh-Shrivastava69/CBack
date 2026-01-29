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
