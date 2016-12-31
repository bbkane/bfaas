#include "bf.h"

int main()
{
    /* char program[] = "++><."; */
    /* char program[] = "[[++]].."; */
    char program[] = "++>+++++[<+>-]>.";
    /* char* program = get_program(argc, argv); */
    bf_interpret(program, 5, NULL, NULL);
}

