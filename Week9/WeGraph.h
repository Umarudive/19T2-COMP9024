// WeGraph.h: an interface for a weighted graph ADT
#include <math.h>

typedef float Weight;             // define a WEIGHT
#define NOWEIGHT  -1.0
#define MAXWEIGHT INFINITY

typedef int Vertex;               // define a VERTEX
#define UNVISITED -1
#define VISITED 1

typedef struct {
    Vertex v;
    Vertex w;
    Weight x;
} Edge;

struct graphRep {
    int nV;       // #vertices
    int nE;       // #edges
    Weight **edges;  // matrix of weights
};
typedef struct graphRep *Graph;   // define a GRAPH

Graph newGraph(int);
void  freeGraph(Graph);
void  showGraph(Graph);

void insertEdge(Edge, Graph);
void removeEdge(Edge, Graph);
void showEdge(Edge);
int  isEdge(Edge, Graph);
Edge newEdge(Vertex, Vertex, Weight);
Edge getEdge(Vertex, Vertex, Graph);
int  cmpEdge(Edge, Edge);

Weight getWeight(Graph, Vertex, Vertex);