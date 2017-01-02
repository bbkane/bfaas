/* This file was automatically generated.  Do not edit! */
#include <stddef.h>
typedef struct bf_input bf_input;
struct bf_input {
    int* input;
    size_t input_len;
    size_t index;
};
typedef struct bf_output bf_output;
typedef int data_type;
struct bf_output {
    data_type* data;
    size_t data_len;
    int* output;
    size_t output_len;
};
void bf_interpret(char *program,size_t data_len,int max_iterations,bf_input *input,bf_output *output);
void print_all_data(data_type *data,size_t data_len);
void print_truncated_data(data_type *data,size_t data_len);
int next_input(bf_input *input);
void print_bf_input(bf_input *input);
void free_bf_input(bf_input *input);
bf_input *malloc_bf_input(int *input,size_t input_len,size_t index);
#define INTERFACE 0
