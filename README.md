# safe_array.h

this is the first version of the library and beacause of that is not prefect 

The challenge of the library is to remove the unsafe aspect of the array in C while maintaining the most important aspect as : direct access, contiguos memory allocation.
For now the array you create is filled from the start to the end. When you want to insert a new item you have to pass the value of the proprieties of the object, not the object itself.

This branch has the porpouse of implementing the capability of multidimensional array. 
The multi dimensional ability of library is working, it's possible to crate a multiple dimensional array, setting a value in a position, getting an element in a posiotion, getting corrent number instantiated
in the array, give the maximum capacity of the array, destroy the array and set the pointer to NULL

Right now the costs of implementing the multidimensional array consist in at least 8 more Bytes needed for the creation of the array,the searching for a pointer in the array given the position need
O(2^n) step where n is the number of dimensions of the array.
Right now i'm considering to implement a thread implementation to reduce the time maybe using a gpu (if present in the machine). Still thinking, need to mesure the medium demension of the array used in
development and if it's worth the multithreading. If necessary i can create a branch for multithreading designed for high dimensions matrix operations(from 10-infinite)



//PROBLEMS
There is still a bug: where you ask for an item in the array, the system will give you a poiter to the data.  with that pointer you can do whatever you want, even exced the limit of the array and go beyong.
The reason for that is that i don't wanna return a copy of the data to not waste memory. 



//NOT IMPLEMENTED

Remove items and adjust the array proprieties conseguently;

//COMPILATION

to compile a program with the library you have to include the header (safe_array.h) in the main 
file and then to compile you have to use the object file (safe_array.o) 
(es. gcc test.c safe_array.o will compile the example program in the repo)
