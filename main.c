#include "bf.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TOOD:
// Expand this to use '-f <file>' and input in the code itself
// Must return a null terminated string
char* get_program(int argc, char** argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <code>\n", argv[0]);
        exit(1);
    }
    char* program = argv[1];
    return program;
}

int main(int argc, char** argv)
{
    /* char program[] = "++><."; */
    /* char program[] = "[[++]].."; */
    /* char program[] = "++>+++++[<+>-]>."; */
    char* program = get_program(argc, argv);
    bf_interpret(program, 5);
}

