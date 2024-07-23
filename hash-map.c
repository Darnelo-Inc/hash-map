#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    HASH_MAP_SUCCESS,
    HASH_MAP_FAILURE,
} hash_map_status;

typedef enum {
    INT,
    FLOAT,
    STRING
} value_t;

typedef struct {
    char* key;
    void* value;
    value_t value_type;
} entry;

//  >70% -> x2

// map.set(...) -> capacity++
// if(capacity > HASH_MAP_SIZE*0.7) malloc(2*HASH_MAP_SIZE);

hash_map_status init_hash_map() {
    const int HASH_MAP_SIZE = 32;

    void* mem = malloc(HASH_MAP_SIZE);
    if(mem == (void*)-1) {
        perror("malloc");
        return HASH_MAP_FAILURE;
    }

    memset(mem, 0, sizeof(entry) * HASH_MAP_SIZE);

    printf("Hash map array starts at: %p\n", mem);

    return HASH_MAP_SUCCESS;
}

size_t getHash(const char* key) {
    size_t hash = 42;
    int c;

    while ((c = *key++)) {
        hash = ((hash << 4) + hash) + c + 42;
    }

    return hash;
}

size_t getIndex(size_t hash, size_t hash_table_size);

int main(void) {
    if(init_hash_map() == HASH_MAP_FAILURE){
        printf("Failed to init hash map.\n");
    };

    printf("Hello, hash map!\n");
    return 0;
}