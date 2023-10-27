#pragma once
#include <stddef.h>

typedef struct array array;

array *new_array_full(unsigned long data_size, unsigned long array_len, 
        void (*print_element)(void *),
        void (*free_element) (void *));
#define new_array(D,L) new_array_full(D,L,NULL,NULL);

int copy_element_in_array(array *this,void *ele_to_insert, unsigned long index);

int move_element_in_array(array *this,void *ele_to_insert, unsigned long index)

void * get_element(array *this, unsigned long index);

int print_array(array *this);
