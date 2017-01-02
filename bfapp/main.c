#include "bf.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LSH_RL_BUFSIZE 1024

// https://brennan.io/2015/01/16/write-a-shell-in-c/
static char *lsh_read_line(void)
{
    size_t bufsize = LSH_RL_BUFSIZE;
    size_t position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Read a character
        c = getchar();

        // If we hit EOF, replace it with a null character and return.
        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        }
        else {
            buffer[position] = (char)c;
        }
        position++;

        // If we have exceeded the buffer, reallocate.
        if (position >= bufsize) {
            bufsize += LSH_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer) {
                fprintf(stderr, "allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}


// TOOD:
// Expand this to use '-f <file>' and input in the code itself
// Must return a null terminated string
static char* get_program(int argc, char** argv)
{
    if (argc == 1) {
        // get code from user
        printf("Enter your bf program\n");
        return lsh_read_line();
    }
    else if (argc == 2) {
        char* program = argv[1];
        return program;
    }
    else {
        fprintf(stderr, "Wrong number of arguments");
        exit(1);
    }

}


int main(int argc, char** argv)
{
    char* program = get_program(argc, argv);
    bf_interpret(program, 5, 1000, NULL, NULL);
}

