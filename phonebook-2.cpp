#include "hash_table.hpp"

int main()
{
    printf("Dada number is quite confusing..., and he said he got a new number.\nI can now store his new number, without replacing the old one.");
    struct HashMap *phonebook = initHashMap(1024);
    insert(phonebook, "mama", "08065354");
    insert(phonebook, "dada", "01566324");
    printf("\nHere's my previous phonebook.\n");
    printMap(phonebook);
    printf("Let me view Dada's previous number for recalling sake.\n");
    printf("Ooh, Here it is. %s\n", get(phonebook, "dada"));
    printf("Okay. Dad's new number is \"01000222\", very easy to recall.\nI can insert it in.\n");
    insert(phonebook, "dada 2", "01000222");
    printMap(phonebook);
    return 0;
}