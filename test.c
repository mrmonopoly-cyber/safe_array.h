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
	void *data; 
	array * this;
	
	unsigned int position[2]={0,0};
	unsigned int dimension[2]={2,3};
	printf("dimensions= %d\t%d\t%d\n",dimension[0],dimension[1],dimension[2]);
	unsigned int value[6] = {1,2,3,4,5,6};
	this = new_array(dimension,2,sizeof(*struct_possible),test_allocation_function);
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

	
	return;
}
