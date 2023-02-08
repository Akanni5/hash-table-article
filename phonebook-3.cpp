#include "hash_table.hpp"

int main()
{
    struct HashMap *phonebook = initHashMap(1024);
    insert(phonebook, "mama", "08065354");
    insert(phonebook, "dada", "01566324");
    insert(phonebook, "dada 2", "01000222");
    printf("Here's my phonebook\n");
    printMap(phonebook);
    printf("I have to remove dada's old number and Also change his name\n");
    char *dada_no = (char *)malloc(sizeof(char) * strlen(get(phonebook, "dada 2")));
    strcpy(dada_no, get(phonebook, "dada 2"));
    remove(phonebook, "dada 2");
    insert(phonebook, "dada", dada_no);
    printMap(phonebook);
    clear(phonebook);
    phonebook = NULL;
    return 0;
}