#ifndef COLLECTIONS_H
#define COLLECTIONS_H

#include "utils.h"

typedef struct cback_hash_node {
    void *key;
    void *value;
    struct cback_hash_node *next;
} cback_hash_node;

// TODO:
typedef struct {
    cback_hash_node ** bucket;
    u32 capacity;
    u32 key_size;
    u32 value_size;
} cback_hash_map;

cback_hash_map *cback_hashmap_create(u32 capacity, u32 key_size,u32 value_size);
void cback_hash_map_put(cback_hash_map *map, void *key,void *value);
int cback_hash_map_get(cback_hash_map *map, void *key,cback_hash_node *out_value);
void cback_hash_map_destroy(cback_hash_map *map);

#endif
