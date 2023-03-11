#ifndef safe_array
#define safe_array

typedef void array;	

// create a new full array with all the position of the array allocated but not instantiated, the funnction you pass is needed for istantiate a value when you need to set an element in the array;
// dimensions_number_size 	: indicate the number of cells of the array
// size_sigle_element		: indicate the sizeof of a single element of the array
// allocation_function		: this function pointer indicate how to give the value to an alement in the array in a specific position 
// 				(es. allocation_value_function(void *position, void *value) in this case i consider an array of integer
// 				{
//					*(int *)position=*(int *) value;
// 				}
//print_element			: this function indicate how to print an element of the array
array *new_array(unsigned int dimensions_number_size,unsigned int size_single_element,void (*print_element) (void *));
//return a poiter to a position of the array
//if the operation is not possible because the position you indicate is out of the array
//the function terminate with return NULL and print in output (stderr) an error message
//otherwise the output of the function is the pointer to the data
extern void *get_element_reference(array *object,unsigned int position); 

//instantiate the values in a specific position of the array
//if the operation is not possible because the position you indicate is out of the array
//the function terminate with return 0 and print in output (stderr) an error message
//otherwise the output of the function is 1
extern unsigned int set_value_in_position(array *object,void *value,unsigned int position); 

extern void destroy(array *object); //destroy the array and put the pointer to NULL

extern void print_array(array *object);
#endif
