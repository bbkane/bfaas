#include "bf.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// makeheaders will put this in the header file
# if INTERFACE
#include <stdbool.h>
#include <stddef.h> // size_t

typedef int data_type;

struct bf_output {
    data_type* data;
    size_t data_len;
    int* output;
    size_t output_len;
    size_t output_index;
};

// use the separate forms of declare and typdef
// so makeheaders doesn't get confused
typedef struct bf_output bf_output;

struct bf_input {
    int* input;
    size_t input_len;
    size_t index;
};

typedef struct bf_input bf_input;

#endif // INTERFACE


bf_output* malloc_bf_output(data_type* data, size_t data_len, int* output, size_t output_len, size_t output_index)
{
    bf_output* ret = malloc(sizeof(bf_output));
    ret->data = data;
    ret->data_len = data_len;
    if(!output) {
        output = malloc(sizeof(int) * output_len);
        memset(output, 0, sizeof(int) * output_len);
    }
    ret->output = output;
    ret->output_len = output_len;
    ret->output_index = output_index;
    return ret;
}


void add_to_bf_output(bf_output* output, int output_to_add)
{
    // TODO: add some fancy realloc stuff here
    // instead of the wraparound
    if (output->output_index == output->output_len) {
        output->output_index = 0;
    }
    output->output[output->output_index] = output_to_add;
    output->output_index += 1;
}


void free_bf_output(bf_output* output)
{
    if (output) {
        free(output->data);
        free(output->output);
        free(output);
    }
}


void print_bf_output(bf_output* output)
{
    print_all_data(output->data, output->data_len);

    for(size_t i = 0; i < output->output_len; ++i)
    {
        printf("%d ", output->output[i]);
    }
    printf("\n");
}


bf_input* malloc_bf_input(int* input, size_t input_len, size_t index)
{
    bf_input* ret = malloc(sizeof(bf_input));
    if (!input) {
        input = malloc(sizeof(int) * input_len);
        // Set the input to zeros if nothing was passed
        memset(input, 0, sizeof(int) * input_len);
        // For testing make it increment
        // TODO: rm
        for(size_t i = 0; i < input_len; i++) {
            input[i] = (int)(i + 1);
        }
    }
    ret->input = input;
    ret->input_len = input_len;
    ret->index = index;
    return ret;
}


void free_bf_input(bf_input* input) {
    if(input) {
        free(input->input);
        free(input);
    }
}


void print_bf_input(bf_input* input) {
    if(input) {
        for(size_t i = 0; i < input->input_len; ++i) {
            printf("%d ", input->input[i]);
        }
        printf("\n");
    }
    else {
        printf("input from stdin\n");
    }
}


int next_input(bf_input* input)
{
    int ret = 0;
    if(input) {
        // assert(input->index == input->input_len);
        // wrap around the input so it makes a legit stream
        if (input->index == input->input_len) {input->index = 0;}
        ret = input->input[input->index];
        input->index += 1;
    }
    else {
        ret = getchar();
    }
    return ret;
}


void print_truncated_data(data_type* data, size_t data_len)
{
    printf("truncated data:\n");
    // get the last non-zero data member
    // TODO: use size_t instead of int
    size_t effective_length = data_len - 1;
    while(effective_length > 0 && data[effective_length] == 0) {
        effective_length--;
    }
    for(size_t i = 0; i <= effective_length; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
}


void print_all_data(data_type* data, size_t data_len)
{
    printf("all data:\n");

    for(size_t i = 0; i < data_len; ++i) {
        printf("%d ", data[i]);
    }
    printf("\n");
}


// making this static because it uses internal state from bf_interpret
static void print_program_state(char* program, char* program_ptr, data_type* data, size_t data_len, data_type* data_ptr, int max_iterations)
{
    char* indent = ":: ";
    printf("%siterations left: %d\n", indent, max_iterations);
    size_t program_len = strlen(program);
    char* program_spot = malloc(sizeof(char) * (program_len + 1));
    memset(program_spot, ' ', program_len);
    program_spot[program_ptr - program] = '^';
    program_spot[program_len] = '\0';
    printf("%s%s\n", indent, program);
    printf("%s%s\n", indent, program_spot);

    data_type* data_spot = malloc(sizeof(data_type) * data_len);
    memset(data_spot, 0, sizeof(data_type) * data_len);
    data_spot[data_ptr - data] = 1;

    printf("%s", indent);
    for(size_t i = 0; i < data_len; ++i) {
        printf("%d ", data[i]);
    }
    printf("\n");
    printf("%s", indent);
    for(size_t i = 0; i < data_len; ++i) {
        if (data_spot[i]) {
            printf("^ ");
        }
        else {
            printf("  ");
        }
    }
    printf("\n\n");

    // TODO: print the data

    free(data_spot);
    free(program_spot);
}


// Interprets a bf program
// Input:
//   program: null terminated bf string
//   data_len: the length of the data array used to interpret the program
//   bf_input, a struct used to describe the input. If it's null, then stdin is used
//      through the getchar() function
//   bf_outpout, a struct used to describe the output. If it's null then stdout is used
//   TODO: add max_steps param
void bf_interpret(char* program, size_t data_len, int max_iterations, bf_input* input, bf_output* output, bool print_debug_info)
{
    size_t program_length = strlen(program);
    char* program_ptr = program;

    // TODO: make this 'infinite' with malloc and realloc
    // The algorithm:
    // make an array with a flag variable in the middle
    // if the data pointer ever reaches the flag variable,
    // make a new array and space the data around the flag pointer again
    // Evenly?
    // data_type data[ARRAY_SIZE] = {0};
    data_type* data = (data_type *)malloc(sizeof(data_type) * data_len);
    memset(data, 0, sizeof(data_type) * data_len);

    data_type* data_ptr = data;

    while (*program_ptr && max_iterations) {
        assert(data_ptr >= data);
        assert(data_ptr <= data + data_len);
        assert(program_ptr >= program);
        // TODO: this may need a +1 to account for the \0 appended
        assert(program_ptr <= program + program_length);

        if (*program_ptr == '>') {
            if (data_ptr == data + data_len - 1) {
                data_ptr = data;
            }
            else {
                data_ptr++;
            }
        }
        else if (*program_ptr == '<') {
            if (data_ptr == data) {
                data_ptr = data + data_len - 1;
            }
            else {
                data_ptr--;
            }
        }
        else if (*program_ptr == '+') { (*data_ptr)++; }
        else if (*program_ptr == '-') { (*data_ptr)--; }
        // TODO: replace %d with %c to print characters
        else if (*program_ptr == '.') {
            if (output) {
                add_to_bf_output(output, *data_ptr);
            }
            else {
                printf("%d\n", *data_ptr);
            }
        }
        else if (*program_ptr == ',') {
            *data_ptr = next_input(input);
        }
        else if (*program_ptr == '[') {
            if (!(*data_ptr)) {
                int pair_count = 1;
                while (pair_count) {
                    program_ptr++;
                    if (*program_ptr == '[') { pair_count++; }
                    if (*program_ptr == ']') { pair_count--; }
                    assert(program_ptr >= program);
                    // TODO: this may need a +1 to account for the \0 appended
                    assert(program_ptr <= program + program_length);
                }
            }
        }
        else if (*program_ptr == ']') {
            if (*data_ptr) {
                int pair_count = 1;
                while (pair_count) {
                    program_ptr--;
                    if (*program_ptr == ']') { pair_count++; }
                    if (*program_ptr == '[') { pair_count--; }
                    assert(program_ptr >= program);
                    // TODO: this may need a +1 to account for the \0 appended
                    assert(program_ptr <= program + program_length);
                }
            }
        }
        if (print_debug_info) {
            print_program_state(program, program_ptr, data, data_len, data_ptr, max_iterations);
        }
        ++program_ptr;
        --max_iterations;
    }
    if (output) {
        output->data = data;
        output->data_len = data_len;
    }
    else {
        print_truncated_data(data, data_len);
        print_all_data(data, data_len);
        free(data);
    }
}

