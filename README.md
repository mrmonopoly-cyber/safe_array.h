# safe_array.h

this is the first version of the library and beacause of that is not prefect 

Right now the system support only one dimensional array; if you wanna create multi dimensional array you to do that manually creating first all the element of one dimension and the use that to create 
a new array which use as object the previos arrays; 

The challenge of the library is to remove the unsafe aspect of the array in C while maintaining the most important aspect as : direct access, contiguos memory allocation.
For now the array you create is filled from the start to the end. When you want to insert a new item you have to pass the value of the proprieties of the object, not the object itself.


//PROBLEMS
There is still a bug: where you ask for an item in the array, the system will give you a poiter to the data.  with that pointer you can do whatever you want, even exced the limit of the array and go beyong.
The reason for that is that i don't wanna return a copy of the data to not waste memory. 



//NOT IMPLEMENTED
Probably i will introduce a filter dependign of the size of the data, if the data is in the size of a block of memory (4096 kB) i will create a copy and return a pointer to the copy. otherwise i will
return the pointer to data itself like now.

I will implement the possibility to create multi dimensional array by default in the creation;


//COMPILATION

to compile a program with the library you have to include the header (safe_array.h) in the main 
file and then to compile you have to use the object file (safe_array.o) 
(es. gcc test.c safe_array.o will compile the example program in the repo)
