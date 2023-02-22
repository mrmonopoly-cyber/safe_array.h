#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef struct array
{
	unsigned int number_items;
 	unsigned int max_amount;
	unsigned int size_single_element;
	unsigned int *dimensions;
	void (*allocation_value_function) (void *,void*);
	void *data;
}array;

array *new_array(unsigned int *dimensions_number_size,unsigned int size_single_element,void (*allocation_value_function) (void *,void *))
{
	assert(dimensions_number_size);
		
	array *this;
	
	unsigned int total_memory=0;
	unsigned int number_of_dimensions=0;
	for(unsigned int *count=dimensions_number_size;*count;count++)
	{
		total_memory+=*count;
		number_of_dimensions++;
	}
	

	this = malloc(sizeof(*this));
	this->size_single_element=size_single_element;
	this->data=malloc(total_memory * size_single_element);
	this->dimensions=malloc((number_of_dimensions) * (sizeof (*this->dimensions)));
	for(unsigned int i=0;i<number_of_dimensions;i++)
	{
		*(this->dimensions+i)=*(dimensions_number_size+i);
	}	
	this->max_amount=*dimensions_number_size;
	this->allocation_value_function=allocation_value_function;

	return this;
}

void *get_element_reference(array *object,unsigned int *position)
{
	assert(object);
	//if(position >= object->max_amount) 
	//{
	//	fprintf(stderr,"error invalid position array\n");
	//	return NULL;
	//}
	unsigned int real_position=0;
	unsigned int relative_pos=0;
	unsigned int temp=0;
	for(unsigned int *t=position;*t;t++)
	{
		relative_pos = *(object->dimensions + temp); 
		real_position+=(*t) * (relative_pos) ;
		temp++;
	}
	return (object->data)+(real_position * object->size_single_element);
}

unsigned int set_value_in_position(array *object,void *value,unsigned int *position)
{
//	assert(object);
//	assert(value);
//	
//	if(position >= object->max_amount)
//	{ 
//		fprintf(stderr,"error invalid position array\n");
//		return 0;
//	}

	unsigned int relative_position=0;
	unsigned int count = 0;
	for(position;*position;position++)
	{
		relative_position+=(*position) * (*(object->dimensions + count));
		count++;
	}

	void * real_position=(object->data) + (relative_position * object->size_single_element);
	

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
