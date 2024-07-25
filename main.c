#include "hash-map.h"
#include <stdio.h>
#include <string.h>

int main(void) {
    hash_map my_map;

    if(init_hash_map(&my_map) == HASH_MAP_FAILURE){
        printf("Failed to init hash map.\n");
    };
    printf("Hello, hash map!\n%p\n", (void*)my_map.entries);

    my_map_set(&my_map, "1", "qwe", sizeof(char) * (strlen("qwe") + 1));
    printf("my_map_has: %s\n", my_map_has(&my_map, "1"));
    printf("my_map_has: %s\n", my_map_has(&my_map, "abob"));
    printf("my_map_get: %p\n", (char*)my_map_get(&my_map, "abob"));
    printf("my_map_get: %s\n", (char*)my_map_get(&my_map, "1"));

    return 0;
}