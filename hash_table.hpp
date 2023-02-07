#ifndef _HASH_TABLE_HPP
#define _HASH_TABLE_HPP

#include <cstdlib>
#include <cstdio>
#include <cstring>

struct HashNode
{
    char *key;
    char *value;
};


struct HashMap
{
    unsigned long size;
    HashNode **array;
};

HashNode *initHashNode(const char *key, const char *value);
// void freeHashNode(HashNode *node);

HashMap *initHashMap(unsigned long int size);

unsigned long int djb2(unsigned char *str);

unsigned long int key_index(const char *key, unsigned long int size);

bool insert(HashMap *hmap, const char *key, const char *value);

void printMap(HashMap *hmap);

char *get(HashMap *map, const char *key);

#endif