// WeGPQ.h                      // different name
#include <stdio.h>
#include <stdlib.h>
#include "WeGraph.h"

//typedef float Weight;             // define a WEIGHT
//typedef int Vertex;               // define a VERTEX


typedef struct pqRep *PQ;

PQ   createPQ(int);             // same
void insertPQ(Edge, PQ);        // an Edge is inserted, not an int
Edge delMinPQ(PQ);              // 'min' not 'max plus returns Edge
int  isEmptyPQ(PQ);             // same
void showPQ(PQ);                // print elements in PQ out