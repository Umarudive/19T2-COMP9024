// IOmem.h
// Interface to IOmem ADT that reads input data, builds and print graphs and manages memory.
#include <stdio.h>
#include <stdlib.h>


int readNumV(void);              // read an int (numV) from stdin
int readBuildGraph();   // read int pairs from stdin
int* mallocArray(int);       // malloc an array of length int * sizeof(int)
void printArray(char *, int *, int); // print an int array of length int

