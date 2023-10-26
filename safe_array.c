#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "safe_array.h"

struct array{
    void *data;
    void *second_element;
    void (*print_element)(void *);
    void (*free_element) (void *);
    unsigned long array_len;
};

//private
static void default_print_element(void * e){

}

static void default_free_element(void * e){

}

//public

array *new_array_full(unsigned long data_size, unsigned long array_len, 
        void (*print_element)(void *),
        void (*free_element) (void *))
{
    array *this = malloc(sizeof *this);
    this->data=malloc(data_size * array_len);
    memset(this->data, 0x0, data_size * array_len);
    this->array_len = array_len;
    this->second_element=this->data+data_size;
    this->print_element=default_print_element;
    if(print_element){
        this->print_element=print_element;
    }
    this->free_element=default_free_element;
    if(free_element){
        this->free_element=free_element;
    }
    
    return this;
}

int copy_element_in_array(array *this,void *ele_to_insert, unsigned long index)
{
    //input error checking
    if(!this){
        goto null_reference_array;
    }
    if(!ele_to_insert){
        goto null_reference_data;
    }
    if(index >= this->array_len){
        goto out_of_boud;
    }

    unsigned long data_size = this->second_element - this->data;
    void *index_to_store = this->data + (index*data_size);
    memset(index_to_store, *(char *)ele_to_insert, data_size);  

    return 0;
    //error handling
null_reference_array:
    fprintf(stderr, "error null reference this\n");
    return -1;
null_reference_data:
    fprintf(stderr, "error null reference ele_to_insert\n");
    return -2;
out_of_boud:
    fprintf(stderr, "error out of bound index %ld\n",index);
    return -3;
}

void * get_element(array *this, unsigned long index)
{
    //input error checking
    if(!this){
        goto null_reference_array;
    }
    if(index >= this->array_len){
        goto out_of_boud;
    }
    
    void *data = this->data;
    unsigned long data_size = this->second_element - data;
    return data + (data_size * index);
//error handling
null_reference_array:
    fprintf(stderr, "error null reference this\n");
    return NULL;
out_of_boud:
    fprintf(stderr, "error out of bound index %ld\n",index);
    return NULL;
}

int print_array(array *this)
{
    if(!this){
        goto null_reference_array;
    }
    
    unsigned int data_size = this->second_element - this->data;
    void *element;
    for(int i=0;i<this->array_len;i++){
        element = this->data + (i*data_size);
        this->print_element(element);
    }

    return 0;
    //error handling
null_reference_array:
    fprintf(stderr, "error null reference this\n");
    return -1;
}
