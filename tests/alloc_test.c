#include "alloc.h"

#include <stdio.h>

int main() {
    cback_arena arena = cback_arena_create(40000);

    int *ptr = cback_arena_alloc(&arena, 10);
    ptr[0] = 2020;
    ptr[1] = 2021;

    printf("%d, %d\n", ptr[0], ptr[1]);

    cback_arena_reset(&arena);
    int *ptr2 = cback_arena_alloc(&arena, 20);
    ptr[0] = 2023;
    ptr[1] = 2024;

    printf("%d, %d\n", ptr[0], ptr[1]);

    cback_arena_destroy(&arena);

    // printf("%d, %d\n", ptr[0], ptr[1]); // segfault
}
