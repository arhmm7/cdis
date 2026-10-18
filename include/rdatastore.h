#ifndef RDATASTORE_H
#define RDATASTORE_H

#define MAX_TABLE_SIZE 100000

extern char* RDATASTORE[MAX_TABLE_SIZE];

void init_table();
unsigned int hash(const char* key);

#endif