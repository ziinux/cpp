Dynamic array
===============

This is an implementation of a dynamic array class

The main file tests the dynamic array implementation

valgrind is used to check memory leaks

To compile use the following commands:
```
cd build
rm -r *
cmake ../
make
```

To run the program and check memory leaks use the folowing command
```
cd build
valgrind --tool=memcheck ./dynamic_array
```


