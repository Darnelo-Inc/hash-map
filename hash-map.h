#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stddef.h>

typedef enum {
    HASH_MAP_SUCCESS,
    HASH_MAP_FAILURE,
} hash_map_status;

typedef struct {
    char* key;
    void* value;
} entry;

typedef struct {
    entry *entries;
    size_t capacity;
    size_t size;
} hash_map;

hash_map_status init_hash_map(hash_map *map);
size_t getHash(const char* key);
size_t getIndex(size_t hash, size_t hash_table_size);

hash_map_status my_map_set(hash_map* map, const char* key, void* value, size_t value_len);

void* my_map_get(hash_map* map, const char* key);
char* my_map_has(hash_map* map, const char* key);

#endif