#include "bf.h"

#include <stdbool.h>
#include <stdio.h>

static void test(char* program, bf_input* input, int max_iterations, bool testme)
{
    if (testme) {
        printf("---\n");
        printf("program: '%s'\n", program);
        printf("input: ");
        print_bf_input(input);
        // hardcoding the data array size
        bf_interpret(program, 5, max_iterations, input, NULL, true);
    }
    else {
        printf("---\n");
        printf("'%s' skipped\n", program);
    }
}

int main()
{
    {
        char* program = "+>+>";
        bf_input* input = malloc_bf_input(NULL, 3, 0);
        test(program, input, 5, false);
        free_bf_input(input);
    }
    {
        char* program = "++[,.>]"; // why is this all zeroes now?
        bf_input* input = malloc_bf_input(NULL, 3, 0);
        test(program, input, 5, false);
        free_bf_input(input);
    }
    {
        char* program = "+[.+]";
        bf_input* input = malloc_bf_input(NULL, 3, 0);
        test(program, input, 100, true);
        free_bf_input(input);
    }
}

