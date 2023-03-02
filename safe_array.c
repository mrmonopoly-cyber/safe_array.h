#include <stdlib.h>
#include <stdio.h>

//private
typedef struct array
{
	unsigned int max_amount;				//max number of items the array can contain
	unsigned int size_single_element;			//sizeof (single element of array) in bytes
	void (*print_element) (void *);				//function to print in stdout a single element 
	void *data;						//pointer to the array
}array;

void allocation_function(void * position,void * value, array *object);

//public

array *new_array(unsigned int dimensions_number_size,unsigned int size_single_element,void (*print_element) (void *));
void *get_element_reference(array *object,unsigned int position);
unsigned int set_value_in_position(array *object,void *value,unsigned int position);
unsigned int get_length(array *object);
void destroy(void *object);
void print_array(array *object);
//implementation
array *new_array(unsigned int dimensions_number_size,unsigned int size_single_element,void (*print_element) (void *))
{
	if(dimensions_number_size == 0 || size_single_element == 0)
	{
		fprintf(stderr,"invalid dimensions_number_size or invalid size_single_element\n");
	}
	array *this;
	
	this = malloc(sizeof(*this));
	this->max_amount=dimensions_number_size;
	this->size_single_element=size_single_element;
	this->data=malloc(dimensions_number_size * size_single_element);
	this->print_element=print_element;
	return this;
}

void *get_element_reference(array *object,unsigned int position)
{
	if(object == NULL)
	{
		fprintf(stderr,"invalid array\n");
		return NULL;
	}
	unsigned int size_element = object->size_single_element;
	if((position * size_element) >= (object->max_amount * size_element)) 
	{
		fprintf(stderr,"error invalid position array\n");
		return NULL;
	}
	return (object->data)+(position*object->size_single_element);
}

unsigned int set_value_in_position(array *object,void *value,unsigned int position)
{
	if(object == NULL || value == NULL)
	{
		fprintf(stderr,"invalid array or invalid value \n");
		return 0;
	}
	unsigned int size_element = object->size_single_element;
	if((position * size_element) >= (object->max_amount * size_element)) 
	{ 
		fprintf(stderr,"error invalid position array\n");
		return 0;
	}
	void * real_position=(object->data) + (position*object->size_single_element);
	allocation_function(real_position,value,object);
	return 1;
}

unsigned int get_length(array *object)
{
	assert(object);
	return object->max_amount;
}

void destroy(void *object)
{
	if(object == NULL)
	{
		fprintf(stderr,"invalid array\n");
		return;
	}
	free(object);
	object=NULL;
}
void print_array(array *object)
{
	if(object == NULL)
	{
		fprintf(stderr,"invalid array\n");
		return;
	}
	unsigned int count = 0;
	void *point_data = NULL;
	for(count =0; count < (object->max_amount * object->size_single_element);count +=object->size_single_element)
	{
		point_data = object->data + count;
		if(point_data != NULL)
		{
			object->print_element(point_data);
			point_data=NULL;
		}else
		{
			printf("NULL\n");
		}
		printf("\n");
	}
}

void allocation_function(void * position,void * value, array *object)
{
	char * cast_position = (char *) position;
	char * cast_value = (char *) value;
	unsigned int size_element = object->size_single_element;
	unsigned int count = 0;

	for(count = 0;count < size_element; count++)
	{
		*(cast_position + count) = *(cast_value + count);
	}	
	return;
}
