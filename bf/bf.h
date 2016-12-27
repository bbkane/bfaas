/* This file was automatically generated.  Do not edit! */
#include <stddef.h>
void bf_interpret(char *program,size_t data_len);
typedef DATA_TYPE data_type;
void print_all_data(data_type *data,size_t data_len);
void print_truncated_data(data_type *data,size_t data_len);
typedef struct bf_return bf_return;
struct bf_return {
    data_type* data;
    size_t data_len;
    int* output;
    size_t output_len;
};
#define INTERFACE 0
