#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"
#include "IOmem.h"
#define UNVISITED -1

int isPath(Graph, Vertex, Vertex, int, int *, int *);

int main (void) {
    int numV;
    if ((numV = readNumV()) > 0) {
        Graph g = newGraph(numV);
        if (readBuildGraph(g)) {
            showGraph(g);
            int *visited = mallocArray(numV);
            int *order = calloc(1, sizeof(int));

            if (isPath(g, 0, 3, numV, order, visited)) {
                printf("found path\n");
            }
            else {
                printf("no path\n");
            }
        }
        g = freeGraph(g);
        g = NULL;
    }
    else {
        printf("Error in reading #number\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int isPath(Graph g, Vertex v, Vertex goalv, int numV, int *order, int *visited) {
    int found = 0;
    visited[v] = *order;
    *order = *order+1;
    if (v == goalv) {
        found = 1;
    }
    else {
        for (Vertex w = 0; w < numV && !found; w++) {
            if (isEdge(g,newEdge(v,w))) {
                if (visited[w] == UNVISITED) {
                    found = isPath(g, w, goalv, numV, order, visited);
                    printf("path %d-%d\n", w, v);
                }
            }
        }
    }
    return found;
}