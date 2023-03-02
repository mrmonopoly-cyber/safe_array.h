#include <stdlib.h>
#include <stdio.h>

//private 
typedef struct array
{
	unsigned int max_amount;				//max number of items that the array is capable of mantain
	unsigned int size_single_element;			//number of bytes needed for a single element of the array
	unsigned int number_of_dimensions;			//number of dimensions of the array
	unsigned int *dimensions;				//array with the size of all dimensions
	void (*print_element) (void *);				//function to print a single element in the array
	void *data;						//array with the data
}array;

int scope_amount(array *object,unsigned int relative_position,unsigned int block);				//return, if possible, the scope amount for the current dimension
void * get_real_position(array * object,unsigned int * position,unsigned int elements_in_array_position);	//return, if possible, the pointer to the position of the array indicated in the array position 
void allocation_function(void *position,void *value, array *object);						//instantiate a single element of the array

//public
array *new_array(unsigned int *dimensions_number_size,unsigned int number_element_array,unsigned int size_single_element,void (*print_element) (void *));
void *get_element_reference(array *object,unsigned int *position,unsigned int elements_in_array_position);
unsigned int set_value_in_position(array *object,void *value,unsigned int *position,unsigned int elements_in_array_position);
unsigned int get_length(array *object);
void destroy(void *object);
void print_array(array *object);
//implementation
array *new_array(unsigned int *dimensions_number_size,unsigned int number_element_array,unsigned int size_single_element,void (*print_element) (void *))
{
	if(dimensions_number_size == NULL || number_element_array == 0  || size_single_element == 0)
	{
		fprintf(stderr,"invalid dimensions array or invalid number_element_array or invalid size_single_element \n");
		return NULL;
	}
		
	array *this;
	unsigned int total_memory=1;
	unsigned int number_of_dimensions=0;
	unsigned int count=0;
	unsigned int temp=0;

	this = malloc(sizeof(*this));
	
	//calculate the total amount to allocate to memorize the array , calculate also the number of dimensions of the array itself 
	for(count=0;count < number_element_array;count++)
	{
		temp = (*(dimensions_number_size + count));
		if(temp == 0)
		{	
			fprintf(stderr,"invalid size dimension\n");
			return NULL;
		}
		total_memory*= temp;
		number_of_dimensions++;
	}

	//instantion of value of this
	this->max_amount=total_memory;
	total_memory*=size_single_element;
	this->size_single_element=size_single_element;
	this->data=malloc(total_memory);
	this->dimensions=malloc((number_of_dimensions) * (sizeof (*this->dimensions)));
	this->number_of_dimensions=number_of_dimensions;
	this->print_element=print_element;
	for(unsigned int i=0;i<number_of_dimensions;i++)
	{
		*(this->dimensions+i)=*(dimensions_number_size + i);
	}	
	
	return this;
}

void *get_element_reference(array *object,unsigned int *position,unsigned int elements_in_array_position)
{
	if(object == NULL)
	{
		fprintf(stderr,"NULL pointer reference for object\n");
		return NULL;
	}
	void *data = get_real_position(object,position,elements_in_array_position);
	if(data == NULL)
	{
		fprintf(stderr,"error retrieving an item in position: ");
		fprintf(stderr,"%d",*(position));
		for(int i =1;i<elements_in_array_position;i++)
		{
			fprintf(stderr,",%d",*(position+i));
		} 
		fprintf(stderr," dimensions of array are: ");
		fprintf(stderr,"%d",*(object->dimensions));
		for(int i =1;i<elements_in_array_position;i++)
		{
			fprintf(stderr,",%d",*(object->dimensions+i));
		} 
		
		fprintf(stderr,"\n");
	}
	return data;
}

unsigned int set_value_in_position(array *object,void *value,unsigned int *position,unsigned int elements_in_array_position)
{
	void *point_data = get_real_position(object,position,elements_in_array_position);
	if(point_data != NULL)
	{
		allocation_function(point_data,value,object);
		return 1;
	}
	fprintf(stderr,"error with the insertion of item\n"); 
	return 0;
}

unsigned int get_length(array *object)
{
	if(object == NULL)
	{
		fprintf(stderr,"NULL pointer reference for object\n");
		return -1;
	}
	return object->max_amount;
}

void destroy(void *object)
{
	if(object == NULL)
	{
		fprintf(stderr,"NULL pointer reference for object\n");
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
	unsigned int count=0;
	void * point_data = NULL;
	unsigned int total_memory=1;
	for(count=0;count < object->number_of_dimensions;count++)
	{
		total_memory*= *(object->dimensions + count);
	}
	for(count=0;count < (total_memory*object->size_single_element);count+=(object->size_single_element))
	{
		point_data = object->data + count;
		if(point_data != NULL)
		{
			object->print_element(point_data);
			point_data=NULL;
		}else
		{
			printf("NULL");
		}
		printf("\n");
	}

}


//ausiliary function
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

void allocation_function(void *position,void *value, array *object)
{
	char * cast_position = (char *) position;
	char * cast_value = (char *) value;
	unsigned int size_element = object->size_single_element;
	unsigned int count = 0;	

	for(count =0;count < size_element;count++)
	{
		*(cast_position + count) = *(cast_value + count);
	}
	return;
}
