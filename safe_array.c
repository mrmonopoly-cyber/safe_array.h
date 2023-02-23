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
void *get_element_reference(array *object,unsigned int *position);
unsigned int set_value_in_position(array *object,void *value,unsigned int *position,unsigned int elements_in_array_position);
unsigned int get_length(array *object);
unsigned int get_current_umount(array *object);
void destroy(void *object);
int scope_amount(array *object,unsigned int relative_position,unsigned int block);

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
		printf("total_memory = %d and single dimension amount=%d\n\n",total_memory,*(dimensions_number_size + count));
	}
	total_memory*=size_single_element;
	printf("total_memory with sizeof = %d\n",total_memory);

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

unsigned int set_value_in_position(array *object,void *value,unsigned int *position,unsigned int elements_in_array_position)
{
	assert(object);
	assert(value);
	
	unsigned int relative_position=0;
	unsigned int count;
	
	for(count =0;count<elements_in_array_position;count++)
	{	
		relative_position+=scope_amount(object,*(position+count),count);
		printf("count=%d\trelative position=%d\tscope amount=%d\n",count,*(position+count),relative_position);
	}

	

	//object->allocation_value_function(real_position,value);
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
	unsigned int scope_amount=1;
	unsigned int index=object->number_of_dimensions-1-block;
	
	for(index;index>0;index--)
	{	
		printf("index=%d\t*(dimesion+index)=%d\n",index,*(object->dimensions+index));
		scope_amount*=*(object->dimensions+index);
	}	

	return relative_position * scope_amount;
}
