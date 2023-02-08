In this article, you will learn what a hash table is, how it is used, and how to create one in C/C++.

## What exactly is a hash table?

A hash table is a form of data structure that stores data associatively. A hash table, also called a hash map, stores data in value and key pairs.

A unique index is assigned to each value. These values are stored in an array format, but each index is distinct in terms of the key associated with the value.

A hash table stores its data in an array, but accessing a value is very fast if you know the value key.

In school, every student has a locker. The lockers are kept somewhere while they are linearly aligned. Each locker is distinct for every student, and there is a key to access it. The student is the key in this situation, and the locker is an index in the array (the locker room). The locker in this situation will also be referred to as "Bucket".

To describe a hash table, we need to know the type of data it can store.

```cpp
struct HashNode
{
    char *key;
    char *value;
};

// method to create a node
struct HashNode *initNode(char *key, char *value)
{
    struct HashNode *hNode;
    // a key cannot be empty.
    if (key == NULL || strlen(key) == 0 || value == NULL) return (NULL);
    hNode = malloc(sizeof(struct HashNode));
    if (hNode == NULL) return (NULL);
    hNode->key = strdup(key);
    hNode->value = strdup(value);
    return (hNode);
}
```

On average, it takes a time complexity of O( 1 ) to search and insert values into a hash map. In my opinion, it is the fastest data structure.

A hash map's time complexity can range from O( 1 ) to O( N ), depending on the technique used to resolve its collision.

### Application

A hash map is used for various reasons, which include:

* A lookup table for compiler operations.
    
* A phonebook.
    
* Cryptography for password verification.
    
* For graphics.
    

A hash map is a preferred data structure due to its efficiency, uniqueness, speed, and scalability.

---

### Hash Functions

A hash table or map without a hash function is unnecessary. A hash function converts a given key into a unique id for the hash table. It is responsible for mapping the key to its value.

A hash function is said to be perfect in the sense that it hardly leads to a hash collision. For this article, I'll be using the djb2 hashing algorithm.

```cpp
/* djb2 hash function */
unsigned long djb2(unsigned char *str)
{
    unsigned long hash = 5381;
    int ch;
    while ((ch = *str++))
        hash = hash * 33 + ch;
    return (hash);
}
```

Now that we have our hash function, let's create the hash map data structure.

```cpp
struct HashMap
{
    int size;
    struct HashNode **array;
};

struct HashMap *initHashMap(int size)
{
    struct HashMap *hMap;
    if (size <= 0) return (NULL);
    hMap = malloc(sizeof(struct HashMap));
    if (!hMap) return (NULL);
    hMap->size = size;
    hMap->array = (struct HashNode **)malloc(sizeof(struct HashNode *) * size);
    if (hMap->array == NULL)
    {
        free(hMap); return (NULL);
    }
    for (int i = 0; i < size; i++)
        hMap->array[i] = NULL;
    return (hMap);
}
```

We also need to write a wrapper function that'll make use of the "djb2" hashing algorithm.

```cpp
unsigned long key_index(const char *key, unsigned long size)
{
    unsigned long hIndex  = djb2((const unsigned char *)key);
    return (hIndex % size);
}
```

---

## **Hash table operations: Insert, Get and Delete.**

It'll be impossible to express the efficiency of a hash table without an example. I'll be creating a method to insert, search, and delete a hash node from a hash table.

### Insert.

Inserting a hash node into a hash table is simple. I'll create a hash node and map its key to a distinct hash index.

A hash node must have a valid key. This means that the key cannot be empty. Though the hash node value can be empty or filled,

Inserting a hash node into a hash map is as quick as inserting a value to the index of an array.

```c
// given an array
#define ARRAY_SIZE 100
int arr_score[ARRAY_SIZE];
// the time complexity of the task below
// is O(1).
arr_score[5] = 67;
```

Same with a hash table; given the key index (5, for instance), it'll be easy to insert a hash node in the hash table.

Here's how to do it:

```cpp
bool insert(struct HashMap *hmap, const char *key, const char *value)
{
    if (!hmap) return false;
    // create the a hash node
    struct HashNode *node = initHashNode(key, value);
    if (!node) return false;
    unsigned long int hIndex = key_index(key, hmap->size);
    if (hmap->array[hIndex] == NULL){
        hmap->array[hIndex] = node;
        return true;
    }
    // if the key already exists I'll replace the value
    // by deleting it and duplicating the new value.
    if (strcmp(hmap->array[hIndex]->key, key) == 0)
    {
        free(node->key);   
        free(node->value);
        free(node);
        node = NULL;
        node = hmap->array[hIndex];
        free(node->value);
        node->value = strdup(value);
        return true;
    }
}
```

The insertion function creates a node and generates its hash index. It checks if the index is empty and adds the new hash node to it. However, in case the index was not empty, as a result of using the same hash key, the value for the index will be replaced.

```cpp
int main()
{
    struct HashMap *phonebook = initHashMap(1024);
    insert(phonebook, "mama", "09065345");
    insert(phonebook, "dada", "01566324");
    printMap(phonebook);
    // OMG!!!! I have to change mama's phone no. she gat a new one! 😲
    insert(phonebook, "mama", "08065354");
    printMap(phonebook);
}
```

Here's our function to print the hash table.

```cpp
void printMap(struct HashMap *hmap)
{
    if (!hmap) return;
    printf("{\n");
    for (int i = 0; i < hmap->size; i++){
        struct HashNode *node = hmap->array[i];
        if (node)
            printf("\t\"%s\" : \"%s\"\n", node->key, node->value);
    }
    printf("}\n");
}
```

### Get

Sometimes, We might want to get the value of a node in a hash table. Given the key, we can easily get the value from the map.

```cpp
const char *value get(struct HashMap *map, const char *key)
{
    if (!map || !key) return (NULL);
    unsigned long hIndex = key_index(key, map->size);
    if (map->array[hIndex] == NULL) return (NULL);
    else
        return map->array[hIndex]->value;
}
```

### Remove

Removing a node from a hash map is also simple. It requires the node key.

```cpp
bool remove(struct HashMap *map, const char *key)
{
    if (!map || !key) return false;
    unsigned long hIndex = key_index(key, map->size);
    struct HashNode *hnode = map->array[hIndex];
    if (hnode){
        free(hnode->key);
        free(hnode->value);
        free(hnode);
        map->array[hIndex] = NULL;
    }
    return true;
}
```

You can find a working example here [https://github.com/Akanni5/hash-table-article/tree/4abff19fedac90c8c88be077d1ec00aaf357479e](https://github.com/Akanni5/hash-table-article/tree/4abff19fedac90c8c88be077d1ec00aaf357479e). It contains three programs, each expressing the use of insert, get and remove operations in a hash table.

## Hash Collision

![two bisons fighting head photo.](https://images.unsplash.com/photo-1552874624-448f857074ee?ixlib=rb-4.0.3&ixid=MnwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8&auto=format&fit=crop&w=870&q=80 align="left")

A hash collision occurs when two or more different keys result in the same hash index. A hash table will not be able to correctly differentiate between the hash keys, resulting in a problem.

> "Hash collisions are no laughing matter, but sometimes you just have to hash it out!"
> 
> \- ChatGPT

For example, this code shows that the key "dram" and "vivency" both map to the same hash key.

```cpp
int main()
{
    char *str1 = "dram";
    char *str2 = "vivency";
    printf("hash index for %s is %ul\n", str1, key_index(str1, 1024));
    printf("hash index for %s is %ul\n", str2, key_index(str2, 1024));
    return (0);
}
```

No hashing algorithm is perfect to eliminate hash collision. A hash collision can only be minimized, nevertheless, a collision is likely to still occur. A few techniques are considered to handle a collision when it occurs.

There are various methods to resolve a hash collision. These include:

* Separate Chaining
    
* Double Hashing
    
* Open Addressing
    
* Linear Probing
    
* Quadratic Probing
    

Each method has its pros and cons. For simplicity, I'll be using the "separate chaining" method.

Separate chaining is a method of resolving hash collisions. In this method, each index or <mark>bucket in a hash table</mark> is treated as a separate linked list. When a collision occurs, the new hash node is added to the list. It can be added to the head of the list or the end of the list. This method allows for quick lookup, but it can decrease the time complexity of the hash table when traversing through the list. With just a little tweak to our previous codes, our collision will be resolved.

```cpp
struct HashNode
{
    struct HashNode *next;
    char *key;
    char *value;  
};

// ... In initHashNode
{
    node->next = NULL;
}
```

Our hash node now functions as a linked list node. Whenever a hash collision occurs, a new hash node is created and inserted into the head of the hash index.

In the insert function, to find a value, I'll have to traverse down the list and compare the key for each key till I find the current key.

```cpp
bool insert(struct HashMap *hmap, const char *key, const char *value)
{
    if (!hmap) return false;
    // create the a hash node
    struct HashNode *node = NULL;
    unsigned long int hIndex = key_index(key, hmap->size);
    if (hmap->array[hIndex] == NULL){
        node = initHashNode(key, value);
        if (!node) return false;
        hmap->array[hIndex] = node;
        return true;
    }
    // if the key already exists I'll replace the value
    // by deleting it and duplicating the new value.
    node = hmap->array[hIndex];
    while (node)
    {
        if (strcmp(node->key, key) == 0){
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
```

Just added a few lines of code to the function. If the key results in a valid hash key, I traverse the list at the hash key, while comparing the keys, if the key already exists, I'll have to replace its value. However, if the key is not found in any of the nodes, I'll have to create a node and add it to the head of the list at the hash index.

Handling a hash collision itself isn't that bad. Remember a collision occurs when two different hash keys map to the same hash bucket. We treat each bucket as a linked list and we kept inserting different hash keys to the head of the list. This might not be the most efficient and best way to handle a collision, however, it encourages simplicity and is maintainable.

The function for getting and removing a hash node from a hash table needs to be updated. You can have this as your task. Here's what you'll do.

```cpp
// Somewhere in the get function
// ...
node = map->array[hIndex];
while (node)
{
    if (strcmp(node->key, key) == 0)
        return node->value;
    node = node->next;
}
return (NULL); // value not found.
```

Here's the function to print the map.

```cpp
void printMap(struct HashMap *hmap)
{
    if (!hmap) return;
    printf("{\n");
    for (int i = 0; i < hmap->size; i++){
        struct HashNode *node = hmap->array[i];
        while (node)
        {
            printf("\t\"%s\" : \"%s\"\n", node->key, node->value);
            node = node->next;
        }
    }
    printf("}\n");
}
```

---

I'm certain you understand what a hash table is, and most of all, you can implement one yourself. A hash table is a common data structure, and without a doubt, it's a useful one. However, If you require some example codes, I've written some here [https://github.com/Akanni5/hash-table-article/tree/main](https://github.com/Akanni5/hash-table-article/tree/main). You can check them.

Thanks for reading this article. Have a nice day 👍.