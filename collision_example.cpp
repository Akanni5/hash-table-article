#include "hash_table.hpp"

int main()
{
    const char *str1 = "dram";
    const char *str2 = "vivency";
    printf("hash index for %s is %llu\n", str1, key_index(str1, 1024));
    printf("hash index for %s is %llu\n", str2, key_index(str2, 1024));
    return (0);
}