#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef struct array
{
	unsigned int number_items;
 	unsigned int max_amount;
	unsigned int size_single_element;
	unsigned int *dimensions;
	unsigned int number_of_dimensions;
	void (*allocation_value_function) (void *,void*);
	void *data;
}array;

array *new_array(unsigned int *dimensions_number_size,unsigned int number_element_array,unsigned int size_single_element,void (*allocation_value_function) (void *,void *));
void *get_element_reference(array *object,unsigned int *position,unsigned int elements_in_array_position);
unsigned int set_value_in_position(array *object,void *value,unsigned int *position,unsigned int elements_in_array_position);
unsigned int get_length(array *object);
unsigned int get_current_umount(array *object);
void destroy(void *object);
int scope_amount(array *object,unsigned int relative_position,unsigned int block);
void * get_real_position(array * object,unsigned int * position,unsigned int elements_in_array_position);

array *new_array(unsigned int *dimensions_number_size,unsigned int number_element_array,unsigned int size_single_element,void (*allocation_value_function) (void *,void *))
{
	assert(dimensions_number_size);
		
	array *this;
	
	unsigned int total_memory=1;
	unsigned int number_of_dimensions=0;
	for(unsigned int count=0;count < number_element_array;count++)
	{
		total_memory*= *(dimensions_number_size + count);
		number_of_dimensions++;
	}
	total_memory*=size_single_element;

	this = malloc(sizeof(*this));
	this->size_single_element=size_single_element;
	this->data=malloc(total_memory);
	this->dimensions=malloc((number_of_dimensions) * (sizeof (*this->dimensions)));
	this->number_of_dimensions=number_of_dimensions;
	for(unsigned int i=0;i<number_of_dimensions;i++)
	{
		*(this->dimensions+i)=*(dimensions_number_size+i);
	}	
	this->max_amount=*dimensions_number_size;
	this->allocation_value_function=allocation_value_function;

	return this;
}

void *get_element_reference(array *object,unsigned int *position,unsigned int elements_in_array_position)
{
	assert(object);
	void *data = get_real_position(object,position,elements_in_array_position);
	return data;
}

unsigned int set_value_in_position(array *object,void *value,unsigned int *position,unsigned int elements_in_array_position)
{
	void * point_data = get_real_position(object,position,elements_in_array_position);
	object->allocation_value_function(point_data,value);
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


int scope_amount(array *object,unsigned int relative_position,unsigned int block)
{
	if(relative_position >= *(object->dimensions + block))
	{
		fprintf(stderr,"error out of bounds\n");
		return -1;
	} 
	unsigned int scope_amount=1;
	for(int i=block+1;i<object->number_of_dimensions;i++)
	{
		scope_amount*=*(object->dimensions + i);
	}
	
	return relative_position * scope_amount;
}

void * get_real_position(array * object,unsigned int * position,unsigned int elements_in_array_position){ 
	unsigned int relative_position=0;
	unsigned int real_position;
	void *point_data;
	unsigned int count;
	int untested_amount;
	for(count =0;count<elements_in_array_position;count++)
	{	
		untested_amount=scope_amount(object,*(position+count),count);
		if(untested_amount!=-1)
		{
			relative_position+=untested_amount;
		}else
		{
			fprintf(stderr,"error out of bounds recognized\nNot gonna instert item\n");
			return NULL;
		}
	}
	real_position=relative_position*object->size_single_element;
	point_data=object->data+real_position;
	return point_data;
}

