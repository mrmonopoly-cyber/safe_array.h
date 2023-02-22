#ifndef safe_array
#define safe_array

typedef void * array;	// the array is NOT omogeneus

array *new_array(unsigned int dimensions_number_size,unsigned int size_single_element,void (*allocation_value_function) (void *,void *)); // create a new full array with all the position of the array allocated but not instantiated, the funnction you pass is needed for istantiate a value when you need to eset an element in the array;
extern void *get_element_reference(array *object,unsigned int position); //get a pointer with a copy od the data in a specific position of the array
extern unsigned int set_value_in_position(array *object,void *value,int position); //instantiate the values in a specific position of the array
extern unsigned int get_length(array *object);	//get the max number of items that you can put in the array
extern unsigned int get_current_umount(array *object);
extern void destroy(void *object); //destroy the array and put the pointer to NULL

#endif
