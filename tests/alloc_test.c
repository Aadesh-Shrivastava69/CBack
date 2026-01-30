#include "alloc.h"

#include <stdio.h>

int main() {
    arena_t arena = arena_create(40000);

    int *ptr = arena_alloc(&arena, 10);
    ptr[0] = 2020;
    ptr[1] = 2021;

    printf("%d, %d\n", ptr[0], ptr[1]);

    arena_reset(&arena);
    int *ptr2 = arena_alloc(&arena, 20);
    ptr[0] = 2023;
    ptr[1] = 2024;

    printf("%d, %d\n", ptr[0], ptr[1]);

    arena_destroy(&arena);

    // printf("%d, %d\n", ptr[0], ptr[1]); // segfault
}
