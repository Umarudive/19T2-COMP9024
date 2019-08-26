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

float *mallocFArray(int numV)
{
    float *p = malloc(numV * sizeof(float));
    for(int i=0;i<numV;i++)
    {
        *(p+i)=INFINITY;
    }
    return p;
}

void showArray(char *text,int *list, int nV)
{
    printf("%s: ", text);
    printf("{");
    for(int i=0; i<nV; i++)
    {
        if(i!=nV-1)
        {
            printf("%d, ", list[i]);
        }
        else
        {
            printf("%d", list[i]);
        }
    }
    printf("}");
    putchar('\n');
}

void showFArray(char *text,float *list, int nV)
{
    printf("%s: ", text);
    printf("{");
    for(int i=0; i<nV; i++)
    {
        if(i!=nV-1)
        {
            printf("%.2f, ", list[i]);
        }
        else
        {
            printf("%.2f", list[i]);
        }
    }
    printf("}");
    putchar('\n');
}

void DijkstraPrim(Graph g, int nV, int nE, Vertex src, char alg) {
    // the last parameter arg is set by main, and is:
    // 'd' for Dijkstra or
    // 'p' for Prim

    int *visited = mallocArray(nV);   // initialised to UNVISITED
    int *parent = mallocArray(nV);    // initialised to UNVISITED
    float *pacost = mallocFArray(nV); // floats: initialised to INFINITY

    pacost[src] = 0.0;
    for (int step = 1; step <= nV; step++) {
        Vertex minw = NONE;
        for (Vertex w = 0; w < nV; w++) {        // find minimum cost vertex
            if ((visited[w] == UNVISITED) &&
                (minw == NONE || pacost[w] < pacost[minw])) {
                minw = w;
            }
        }


        visited[minw] = VISITED;

        for (Vertex w = 0; w < nV; w++) {         //
            Weight minCost = getWeight(g, minw, w);// if minw == w, minCost = NOWEIGHT
            // minCost is cost of the minimum crossing edge
            if (minCost != NOWEIGHT) {
                if (alg == 'd') {                     // if DIJKSTRA ...
                    minCost = minCost + pacost[minw]; // add in the path cost
                }

                if ((visited[w] != VISITED) &&
                    (minCost < pacost[w])) {
                    pacost[w] = minCost;
                    parent[w] = minw;
                }
            }
        }

        printf("min: %d\n",minw);     // set minw as temperate parent node
        showArray("parent", parent, nV);
        showFArray("pacost", pacost, nV);
        putchar('\n');


    }
    showArray("visited", visited, nV);
    showArray("parent", parent, nV);
    showFArray("pacost", pacost, nV);
    free(visited);
    free(parent);
    free(pacost);
    return;
}


int main(void)
{
    Graph g;
    char * temp = malloc(1024);
    memset(temp,0,1024);
    int i = 0;
    Vertex v = 0;
    Vertex w = 0;
    Weight x = 0;
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

    showGraph(g);
    // if p use prim
    // if d use dijkstra
    DijkstraPrim(g,nV,nE,0,'p');
    free(temp);
    freeGraph(g);
    g=NULL;
    return 0;
}