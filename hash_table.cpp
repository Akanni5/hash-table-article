#include "hash_table.hpp"

HashNode *initHashNode(const char *key, const char *value)
{
    HashNode *hNode = NULL;
    // a key cannot be empty.
    if (key == NULL || strlen(key) == 0 || value == NULL)
        return (NULL);
    hNode = (HashNode *)malloc(sizeof(struct HashNode));
    if (hNode == NULL)
        return (NULL);
    hNode->key = strdup(key);
    hNode->value = strdup(value);
    hNode->next = NULL;
    return (hNode);
}

HashMap *initHashMap(unsigned long int size)
{
    HashMap *hMap;
    if (size <= 0)
        return (NULL);
    hMap = (HashMap *)malloc(sizeof(struct HashMap));
    if (!hMap)
        return (NULL);
    hMap->size = size;
    hMap->array = (struct HashNode **)malloc(sizeof(struct HashNode *) * size);
    if (hMap->array == NULL)
    {
        free(hMap);
        return (NULL);
    }
    for (int i = 0; i < size; i++)
        hMap->array[i] = NULL;
    return (hMap);
}

unsigned long int djb2(unsigned char *str)
{
    unsigned long int hash = 5381;
    int ch;
    while ((ch = *str++)) hash = hash * 33 + ch;
    return hash;
}

unsigned long int key_index(const char *key, unsigned long int size)
{
    unsigned long int hash = djb2((unsigned char *)key);
    return hash % size;
}

bool insert(HashMap *hmap, const char *key, const char *value)
{
    if (!hmap)
        return false;
    // create the a hash node
    struct HashNode *node = NULL;
    unsigned long int hIndex = key_index(key, hmap->size);
    if (hmap->array[hIndex] == NULL)
    {
        node = initHashNode(key, value);
        if (!node)
            return false;
        hmap->array[hIndex] = node;
        return true;
    }
    // if the key already exists I'll replace the value
    // by deleting it and duplicating the new value.
    node = hmap->array[hIndex];
    while (node)
    {
        if (strcmp(node->key, key) == 0)
        {
            free(node->value);
            node->value = strdup(node->value);
            return true;
        }
        node = node->next;
    }
    // at this point, the hash node for the hash key does not exist. though, the hash key exists.
    // I'll add the new node to the head.
    node = initHashNode(key, value);
    if (!node) return false;
    node->next = hmap->array[hIndex];
    hmap->array[hIndex] = node;
    return true;
}

void printMap(HashMap *hmap)
{
    if (!hmap)
        return;
    printf("{\n");
    for (int i = 0; i < hmap->size; i++)
    {
        struct HashNode *node = hmap->array[i];
        while (node)
        {
            printf("\t\"%s\" : \"%s\"\n", node->key, node->value);
            node = node->next;
        }
    }
    printf("}\n");
}

const char *get(HashMap *map, const char *key)
{
    if (!map || !key)
        return (NULL);
    unsigned long hIndex = key_index(key, map->size);
    HashNode *node = map->array[hIndex];
    while (node)
    {
        if (strcmp(node->key, key) == 0)
            return node->value;
        node = node->next;
    }
    return (NULL);
}

bool remove(struct HashMap *map, const char *key)
{
    if (!map || !key)
        return false;
    unsigned long hIndex = key_index(key, map->size);
    HashNode *hnode = map->array[hIndex];
    HashNode *next = NULL;
    // if at the beginning.
    if (hnode && strcmp(hnode->key, key) == 0)
    {
        next = hnode->next;
        free(hnode->key);
        free(hnode->value);
        free(hnode);
        map->array[hIndex] = next;
        return true;
    }
    next = hnode->next;
    while (next)
    {
        if (strcmp(next->key, key) == 0)
        {
            hnode->next = next->next;
            free(next->key);
            free(next->value);
            free(next);
            return true;
        }
        hnode = next;
        next = next->next;
    }
    return false;
}

void clear(HashMap *map)
{
    if (!map)   return;
    HashNode *node = NULL;
    HashNode *next = NULL;

    for (unsigned long int i = 0; i < map->size; i++)
    {
        node = map->array[i];

        while (node)
        {
            next = node->next;
            free(node->value);
            free(node->key);
            free(node);
            node = NULL;
            node = next;
        }
    }

    free(map->array);
    free(map);
    map = (HashMap *)0;
}