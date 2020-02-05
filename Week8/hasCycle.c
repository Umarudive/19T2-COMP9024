// hasCycle.c: search for a cycle in a graph using DFS
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "IOmem.h"

#define UNVISITED -1
#define STARTVERTEX 0

void searchForCycle(Graph, int, int);
int hasCycle(Graph, int, Vertex, Vertex, int *, int *);

int main(void) {
    int numV;
    if ((numV = readNumV()) > 0) {        // read #vertices
        Graph g = newGraph(numV);
        if (readBuildGraph(g) == 1) {
            showGraph(g);

            searchForCycle(g, STARTVERTEX, numV);
        }
        freeGraph(g);
        g= NULL;
    }
    else {
        printf("Error in reading #number\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

// a wrapper for the recursive call to hasCycle()
void searchForCycle(Graph g, int v, int numV) {
    int *visited = mallocArray(numV);
    int order = 0;

    if (hasCycle(g, numV, v, v, &order, visited)) {
        printf("found a cycle\n");
    }
    else {
        printf("no cycle found\n");
    }
    printArray("Visited ", visited, numV);
    free(visited);
    return;
}

int hasCycle(Graph g, int numV, Vertex fromv, Vertex v, int *order, int *visited) {
    int retval = 0;
    visited[v] = *order;
    *order = *order+1;
    for (Vertex w = 0; w < numV && !retval; w++) {
        if (isEdge(g,newEdge(v,w))) {
            if (visited[w] == UNVISITED) {
                printf("traverse edge %d-%d\n", v, w);
                retval = hasCycle(g, numV, v, w, order, visited);
            }
            else {
                if (w != fromv) { // exclude the vertex we've just come from
                    // WE HAVE REVISITED A VERTEX ==> CYCLE
                    printf("traverse edge %d-%d\n", v, w);
                    retval = 1;
                }
            }
        }
    }
    return retval;
}