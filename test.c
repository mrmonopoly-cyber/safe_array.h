#include <stdio.h>
#include <stdlib.h>
#include "safe_array.h"


struct test
{
	int a;
};


void debug_object();
void print_test(void *input);

void main()
{
	debug_object();
	
} 

void print_test(void *input)
{
	struct test *point_data = (struct test *) input;
	printf("%d\n",point_data->a);
}
void debug_object()
{	
	struct test *struct_possible;
	char *possible_out;
 	array * this;
	
	unsigned int position=0;
	unsigned int dimension =5;
	unsigned int value[5] = {1,2,3,4,5};
	this = new_array(dimension,sizeof(*struct_possible),print_test);
	
	for(position;position<dimension;position++)
	{	
		set_value_in_position(this,&value[position],position);
	}
	for(position=0;position<dimension;position++)
	{
		possible_out = get_element_reference(this,position);
		if(possible_out != NULL)
		{	
			struct test *vt = (struct test *)possible_out;
			printf("value %d in position %d of array\n",vt->a,position);
			possible_out = NULL;
		}
	}
	print_array(this);
	return;
}
