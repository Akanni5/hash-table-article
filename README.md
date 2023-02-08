# HASH TABLE
This is the source code repository for the article I created on hashnode.com on hash tables.

To run the program, you have to compile it using a C++ compiler. I use g++ to compile mine.

```
hash-table $ ls
collision_example.cpp hash_table.cpp  
hash_table.hpp  phonebook-2.cpp
phonebook-3.cpp  phonebook.cpp  README.md
```

You can compile each example file this way:
```
# don't do this
hash-table $ g++ hash_table.cpp <example_file> -o <output>
# do this
hash-table $ g++ hash_table.cpp phonebook.cpp -o phonebook
```
Be sure to read each example code to understand how it works.