#include <stdio.h>
#include <stdlib.h>
#include "safe_array.h"


struct test
{
	int a;
};


void test_allocation_function(void *position,void *data);
void debug_object();

void main()
{
	debug_object();
	//size_t l=10;
	//size_t m=20;
	//size_t n=30;
	//void *d3d = calloc(l*m*n, sizeof(double));
	//for(int j=0;j<(l*m*n);j+=sizeof(double))
	//{
	//	*((double *)(d3d +j)) = j;
	//}		
	//for(int j=0;j<(l*m*n);j+=sizeof(double))
	//{
	//	printf("%lf\n",*((double *)(d3d +j)));
	//}	
} 


void test_allocation_function(void *position,void *data)
{
	((struct test *)position)->a=*(int *)data;
}

void debug_object()
{	
	struct test *struct_possible;
	char *possible_out;
 	array * this;
	
	unsigned int position[3]={4,1,2};
	unsigned int dimension[3]={5,2,3};
	printf("dimensions= %d\t%d\t%d\n",dimension[0],dimension[1],dimension[2]);
	unsigned int value[5] = {1,2,3,4};
	this = new_array(dimension,3,sizeof(*struct_possible),test_allocation_function);
	printf("allocation complete\n");
	
	set_value_in_position(this,&value[2],position,3);

	//struct test * data = (struct test *) get_element_reference(this,position);
	//printf("first element of array= %d\n",data->a);
	
	return;
}
