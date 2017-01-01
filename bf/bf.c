#include "bf.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// makeheaders will put this in the header file
# if INTERFACE
#include <stddef.h> // size_t

typedef int data_type;

// is this the right approach?
struct bf_output {
    data_type* data;
    size_t data_len;
    int* output;
    size_t output_len;
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

bf_input* malloc_bf_input(int* input, size_t input_len, size_t index) {
    bf_input* ret = malloc(sizeof(bf_input));
    if (input) {
        ret->input = input;
    }
    else {
        input = malloc(sizeof(int) * input_len);
        // Set the input to zeros if nothing was passed
        memset(input, 0, sizeof(int) * input_len);
    }
    ret->input_len = input_len;
    ret->index = index;
    return ret;
}


void free_bf_input(bf_input* input) {
    free(input->input);
    free(input);
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

    for(size_t i = 0; i < data_len; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
}

// Interprets a bf program
// Input:
//   program: null terminated bf string
//   data_len: the length of the data array used to interpret the program
//   bf_input, a struct used to describe the input. If it's null, then stdin is used
//      through the getchar() function
//   bf_outpout, a struct used to describe the output. If it's null then stdout is used
//   TODO: add max_steps param
void bf_interpret(char* program, size_t data_len, bf_input* input, bf_output* output)
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

    while (*program_ptr) {
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
            printf("%d\n", *data_ptr);
        }
        else if (*program_ptr == ',') {
            if (input) {
                *data_ptr = input->input[input->index];
                input->index += 1;
                // assert(input->index == input->input_len);
                // For convenience, I'm going to just wrap the input around
                if (input->index == input->input_len) {input->index = 0;}
            }
            else {
                *data_ptr = getchar();
            }
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
        program_ptr++;
    }
    print_truncated_data(data, data_len);
    print_all_data(data, data_len);
    free(data);
}

