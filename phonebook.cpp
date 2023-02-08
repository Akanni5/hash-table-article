#include "hash_table.hpp"

int main()
{
    struct HashMap *phonebook = initHashMap(1024);
    insert(phonebook, "mama", "09065345");
    insert(phonebook, "dada", "01566324");
    printMap(phonebook);
    // OMG!!!! I have to change mama's phone no. she gat a new one! 😲
    insert(phonebook, "mama", "08065354");
    printMap(phonebook);
    printf("%p\n", &phonebook->size);
    clear(phonebook);
    phonebook = NULL;
    return 0;
}