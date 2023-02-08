#include "hash_table.hpp"

int main()
{
    HashMap *map = initHashMap(1024);
    insert(map, "dram", "cool1");
    insert(map, "vivency", "cool2");
    printMap(map);
    remove(map, "vivency");
    const char *value = get(map, "vivency");
    if (value)
        printf("%s\n", value);
    value = get(map, "dram");
    printf("%s\n", value);
    printMap(map);
    return 0;
}