#include "bf.h"

#include <stdio.h>

static void test(char* program, bf_input* input, int max_iterations)
{
    printf("---\n");
    printf("program: '%s'\n", program);
    printf("input: ");
    print_bf_input(input);
    bf_interpret(program, 5, max_iterations, input, NULL);
    printf("---\n");
}

int main()
{
    /* char* program = ",.>,."; */
    {
        char* program = "[,.>]"; // why is this all zeroes now?
        bf_input* input = malloc_bf_input(NULL, 3, 0);
        test(program, input, 5);
        free_bf_input(input);
    }
    {
        char* program = "+[.+]";
        bf_input* input = malloc_bf_input(NULL, 3, 0);
        test(program, input, 100);
        free_bf_input(input);
    }
}

