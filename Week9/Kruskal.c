#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "WeGPQ.h"

#define UNVISITED -1
#define VISITED 1
#define NONE -1

int *mallocArray(int numV)
{
    int *p = malloc(numV * sizeof(int));
    for(int i=0;i<numV;i++)
    {
        *(p+i) = UNVISITED;
    }
    return p;
}

int isPath(Graph g, int curv, int goal, int numV, int *order, int *visited) {
// starting at 'curv', do a recursive DFS looking for vertex 'goal'
    int found = 0;
    visited[curv] = *order;
    *order = *order+1;
    if (curv == goal) {
        found = 1;
    }
    else {
        for (Vertex w=0; w < numV && !found; w++) {
            if (isEdge(newEdge(curv, w, 0.0), g)) {
                if (visited[w]==UNVISITED) {
                    found = isPath(g, w, goal, numV, order, visited);
                }
            }
        }
    }
    return found;
}

Graph kruskal(Graph g, int nV, int nE) {
    Graph mst = newGraph(nV);
    PQ p = createPQ(nE+1);
    Vertex v1;
    for (v1 = 0; v1 < nV; v1++) { // insert all the edges into the PQ
        Vertex v2;
        for (v2 = v1; v2 < nV; v2++) {
            Edge e = getEdge(v1, v2, g);
            if (isEdge(e, g))
            {
                insertPQ(e, p);
            }
        }
    }
    //showPQ(p);  for debug

    int n = 0;  // counts the number of edges
    Weight cost = 0.0;
    while (!isEmptyPQ(p) && n < nV-1) {
        Edge e = delMinPQ(p); // delete an edge and return the edge with smallest weight first
        //
        int *visited = mallocArray(nV);
        int order = 0;
        // ispath = 0 indicate no cycle in path
        if (isPath(mst, e.v, e.w, nV, &order, visited) == 0) {
            insertEdge(e, mst);
            printf("Accept ");
            showEdge(e);
            putchar('\n');
            cost += e.x;
            n++;
        }
        // cycle existed
        else {
            printf("Reject ");
            showEdge(e);
            putchar('\n');
        }
        free(visited);
    }
    printf("\tTotal cost = %f\n", cost);
    return mst;
}

int main(void)
{
    Graph g = NULL;
    char * temp = malloc(1024);
    memset(temp,0,1024);
    int i = 0;
    Vertex v = 0;
    Vertex w = 0;
    Weight x = 0.0;
    while(fgets(temp, 1024, stdin))
    {
        if(i==0)
        {
            g=newGraph(atoi(temp));
        }
        else
        {
            int t=0;
            char *str = strtok(temp," :");
            while(str)
            {
                if(t==0)
                {
                    v = atoi(str);
                }
                else if(t==1)
                {
                    w = atoi(str);
                }
                else
                {
                    x = atof(str);
                }

                if(t==2)
                {
                    Edge e = {v,w,x};
                    insertEdge(e,g);
                    t=0;
                }
                else
                {
                    t++;
                }
                str = strtok(NULL," :");
            }
        }
        i=1;
    }
    int nV = g->nV;
    int nE = g->nE;

    Graph new_mst = kruskal(g,nV,nE);
    showGraph(new_mst);

    free(temp);
    freeGraph(g);
    g=NULL;
    return 0;
}