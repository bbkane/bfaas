/* This file was automatically generated.  Do not edit! */
#include <stddef.h>
typedef struct bf_input bf_input;
struct bf_input {
    int* input;
    size_t input_len;
};
typedef struct bf_output bf_output;
typedef DATA_TYPE data_type;
struct bf_output {
    data_type* data;
    size_t data_len;
    int* output;
    size_t output_len;
};
void bf_interpret(char *program,size_t data_len,bf_input *bf_input,bf_output *bf_output);
void print_all_data(data_type *data,size_t data_len);
void print_truncated_data(data_type *data,size_t data_len);
bf_input *init_bf_input(size_t input_len);
#define INTERFACE 0
