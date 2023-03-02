#ifndef safe_array
#define safe_array

typedef void array;

// create a new full array with all the position of the array allocated but not instantiated, the funnction you pass is needed for istantiate a value when you need to set an element in the array;
// dimensions_number_size 			: an array that indicate the number of cells of each dimension of array
// number_of_elements_array_dimension_size	: indicate the numbero of elements in the array dimensions_number_size; 
// size_sigle_element				: indicate the sizeof of a single element of the array
// 							(es. allocation_value_function(void *position, void *value) in this case i consider an array of integer
// 							{
//								*(int *)position=*(int *) value;
// 							}
//print_element					: this function is needed to say the system how to print in stdout the an element of the array
array *new_array(unsigned int *dimensions_number_size,unsigned int number_element_array,unsigned int size_single_element,void (*print_element) (void *));
//return a poiter to a position of the array
//if the operation is not possible because the position you indicate is out of the array
//the function terminate with return NULL and print in output (stderr) an error message
//otherwise the output of the function is the pointer to the data
extern void *get_element_reference(array *object,unsigned int *position); 

//instantiate the values in a specific position of the array
//if the operation is not possible because the position you indicate is out of the array
//the function terminate with return 0 and print in output (stderr) an error message
//otherwise the output of the function is 1
unsigned int set_value_in_position(array *object,void *value,unsigned int *position);

//return the the max number of items you can store in the array
extern unsigned int get_length(array *object);	

//destroy the array e set the pointer to NULL
extern void destroy(array *object); 

//print all the element in the array 
void print_array(array *object);
#endif
