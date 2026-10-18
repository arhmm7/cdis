#include <stddef.h>
#include <string.h>
#include "rdatastore.h"

char* RDATASTORE[MAX_TABLE_SIZE];

void init_table() {
    for(int i = 0; i < MAX_TABLE_SIZE; i++) {
        RDATASTORE[i] = NULL;
    }
}

unsigned int hash(const char* key) {
    unsigned int key_len = strlen(key);
    unsigned int hash_value = 0;
    for(int i = 0; i < key_len; i++) {
        hash_value = hash_value * 31 + (unsigned char)key[i];
    }
    return hash_value % MAX_TABLE_SIZE;
}
