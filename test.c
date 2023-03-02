#include <stdio.h>
#include <stdlib.h>
#include "safe_array.h"


struct test
{
	int a;
};


void test_allocation_function(void *position,void *data);
void debug_object();
void print_el_test(void * input);
void main()
{
	debug_object();
} 

void print_el_test(void * input)
{
	struct test *data=(struct test *) input;
	printf("%d\n",data->a); 
}
void debug_object()
{	
	struct test *struct_possible;
	char *possible_out;
	void *data; 
	array * this;
	
	unsigned int position[2]={3,0};
	unsigned int dimension[2]={4,5};
	printf("dimensions= %d\t%d\t%d\n",dimension[0],dimension[1],dimension[2]);
	unsigned int value[6] = {1,2,3,4,5,6};
	this = new_array(dimension,2,sizeof(*struct_possible),print_el_test);
	printf("allocation complete\n");
	printf("max amount element in array =%d\n",get_length(this));
	

	for(int i=0;i<5;i++)
	{
		printf("inserting element in position 0 %d wich is %d\n",i,value[i]); 
		set_value_in_position(this,&value[i],position,2);
		position[1]++;
	}
	position[1]=0;
	for(int i=0;i<5;i++)
	{
		data=get_element_reference(this,position,2);
		if(data!=NULL)printf("%d-th element of array is %d\n",i,((struct test *)data)->a);
		position[1]++;
		data=NULL;
	}
	print_array(this);
	
	return;
}
