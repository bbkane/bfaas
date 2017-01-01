#include "bf.h"

int main()
{
    /* char program[] = "++><."; */
    /* char program[] = "[[++]].."; */
    /* char program[] = "++>+++++[<+>-]>."; */
    /* char* program = get_program(argc, argv); */
    /* char* program = ",.>,."; */
    char* program = "[,.>]"; // why is this all zeroes now?
    bf_input* input = malloc_bf_input(NULL, 3, 0);
    bf_interpret(program, 5, input, NULL);
}

