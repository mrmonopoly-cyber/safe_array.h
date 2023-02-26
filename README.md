# safe_array.h

this is the first version of the library and beacause of that is not prefect 


The challenge of the library is to remove the unsafe aspect of the array in C while maintaining the most important aspect as : direct access, contiguos memory allocation.
For now the array you create is filled from the start to the end. When you want to insert a new item you have to pass the value of the proprieties of the object, not the object itself.


//FEATURES
Right now the system is capable of creating a mono dimensional array,setting values of data in the array, getting a pointer to an element in the array, destroy the array, get the size of the array.
The step needed to access to an item in the array is constant and consists in 2 steps: 
    1 - access the object itself 
    2 - access to the item you wanna know.(if you need a proprieties of the array you only need 1 step to access it)

//PROBLEMS
There is still a bug: where you ask for an item in the array, the system will give you a poiter to the data.  with that pointer you can do whatever you want, even exced the limit of the array and go beyong.
The reason for that is that i don't wanna return a copy of the data to not waste memory. 



//NOT IMPLEMENTED
Probably i will introduce a filter dependign of the size of the data, if the data is in the size of a block of memory (4096 kB) i will create a copy and return a pointer to the copy. otherwise i will
return the pointer to data itself like now.

Possibility to remove an element from the array and adjust the proprieties.




//COMPILATION

to compile a program with the library you have to include the header (safe_array.h) in the main 
file and then to compile you have to use the object file (safe_array.o) 
(es. gcc test.c safe_array.o will compile the example program in the repo)
