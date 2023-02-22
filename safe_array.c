#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef struct array
{
	unsigned int number_items;
 	unsigned int max_amount;
	unsigned int size_single_element;
	void (*allocation_value_function) (void *,void*);
	void *data;
}array;

array *new_array(unsigned int dimensions_number_size,unsigned int size_single_element,void (*allocation_value_function) (void *,void *))
{
	assert(dimensions_number_size);
		
	array *this;

	this = malloc(sizeof(*this));
	this->size_single_element=size_single_element;
	this->data=malloc(dimensions_number_size * size_single_element);
	this->max_amount=dimensions_number_size;
	this->allocation_value_function=allocation_value_function;
	return this;
}

void *get_element_reference(array *object,unsigned int position)
{
	if(position >= object->max_amount) 
	{
		fprintf(stderr,"error invalid position array\n");
		return NULL;
	}
	return (object->data)+(position*object->size_single_element);
}

unsigned int set_value_in_position(array *object,void *value,unsigned int position)
{
	assert(object);
	assert(value);
	
	if(position >= object->max_amount)
	{ 
		fprintf(stderr,"error invalid position array\n");
		return 0;
	}
	void * real_position=(object->data) + (position*object->size_single_element);
	object->allocation_value_function(real_position,value);
	object->number_items++;

	return 1;
}

unsigned int get_length(array *object)
{
	assert(object);
	return object->max_amount;
}

unsigned int get_current_umount(array *object)
{
	assert(object);
	return ((array *) object)->number_items;
}

void destroy(void *object)
{
	assert(object);
	free(object);
	object=NULL;
}
