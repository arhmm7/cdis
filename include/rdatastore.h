#ifndef RDATASTORE_H
#define RDATASTORE_H

#define MAX_TABLE_SIZE 100000

char* RDATASTORE[MAX_TABLE_SIZE];

unsigned int hash(const char* key);

#endif