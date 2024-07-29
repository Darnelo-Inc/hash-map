#include "hash-map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

hash_map_status init_hash_map(hash_map* map) {
	const int HASH_MAP_SIZE = 10000;

	map->entries = malloc(sizeof(entry) * HASH_MAP_SIZE);
	if (map->entries == NULL) {
		perror("malloc");
		return HASH_MAP_FAILURE;
	}

	map->capacity = HASH_MAP_SIZE;
	map->size = 0;

	memset(map->entries, 0, sizeof(entry) * HASH_MAP_SIZE);

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

size_t getIndex(size_t hash, size_t hash_table_size) {
	return hash % hash_table_size;
}

hash_map_status my_map_set(hash_map* map, const char* key, void* value, size_t value_len) {
	if (map->size >= map->capacity) {
		return HASH_MAP_FAILURE;
	}

	size_t hash = getHash(key);
	size_t index = getIndex(hash, map->capacity);

	while (map->entries[index].key != NULL && strcmp(map->entries[index].key, key) != 0) {
		index = (index + 1) % map->capacity;
	}

	if (map->entries[index].key == NULL) {
		map->entries[index].key = strdup(key);

		if (map->entries[index].key == NULL) {
			return HASH_MAP_FAILURE;
		}

		map->size++;
	} else {
		free(map->entries[index].value);
	}

	map->entries[index].value = malloc(value_len);

	if (map->entries[index].value == NULL) {
		return HASH_MAP_FAILURE;
	}

	memcpy(map->entries[index].value, value, value_len);

	return HASH_MAP_SUCCESS;
}

void* my_map_get(hash_map* map, const char* key) {
	size_t hash = getHash(key);
	size_t index = getIndex(hash, map->capacity);
	size_t startIndex = index;

	while (map->entries[index].key != NULL && strcmp(map->entries[index].key, key) != 0) {
		index = (index + 1) % map->capacity;

		if (index == startIndex) {
			return NULL;
		}
	}

	return map->entries[index].value;
}

char* my_map_has(hash_map* map, const char* key) {
	size_t hash = getHash(key);
	size_t index = getIndex(hash, map->capacity);
	size_t startIndex = index;

	if (map->entries[index].key == NULL) {
		return "false";
	}

	while (strcmp(map->entries[index++].key, key) != 0) {
		index = index % map->capacity;

		if (index == startIndex || map->entries[index].key == NULL) {
			return "false";
		}
	}

	return "true";
}

char* convertIntToString(int a) {
	char* s = malloc(5 * sizeof(char));
	s[0] = (a & 255);
	s[1] = ((a >> 8) & 255);
	s[2] = ((a >> 16) & 255);
	s[3] = ((a >> 24) & 255);

	for(int i = 0; i < 4; ++i) {
		if(s[i] == '\0') {
			s[i] = '$';
		}
	}

	s[4] = '\0';

	return s;
}