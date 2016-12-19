#ifndef BF_H
#define BF_H

#define ARRAY_SIZE 30

// pass in a larger data type at compile time with -DDATA_TYPE=<type>
// Ex: -DDATA_TYPE=int
#ifndef DATA_TYPE
# define DATA_TYPE char
#endif

typedef DATA_TYPE data_type;

#undef DATA_TYPE

void print_truncated_data(data_type* data);
void print_all_data(data_type* data);
void bf_interpret(char* program);
#endif
