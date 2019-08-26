// pqHP.c: priority queue implementation for pq.h using a heap
#include "WeGPQ.h"

// Priority queue implementation using an unordered array
struct pqRep {
    int nItems;  // actual count of Items
    Edge *items;  // array of Items
    int maxsize; // maximum size of array
};


// fix up the heap for the 'new' element child
static void fixUp(Edge *heap, int child) {
    while (child>1 && heap[child/2].x > heap[child].x) {
        Edge swap = heap[child];         // if parent < child, do a swap
        heap[child] = heap[child/2];
        heap[child/2] = swap;
        child = child/2;                // become the parent
    }
    return;
}

// force value at a[par] into correct position
static void fixDown(Edge *heap, int par, int len) {
    int finished = 0;
    while (2*par<=len && !finished) {// as long as you are within bounds
        int child = 2*par;          // the first child is here
        if (child<len && heap[child].x > heap[child+1].x) {
            child++;                 // choose smaller of two children
        }
        if (heap[par].x > heap[child].x) { // if node is larger than this child ...
            Edge swap = heap[child];   // if parent < child, do a swap
            heap[child] = heap[child/2];
            heap[child/2] = swap;
            par = child;             // ... and become this child
        }
        else {
            finished = 1;            // else we do not have to go any further
        }
    }
    return;
}


PQ createPQ(int size) {
    PQ q = malloc(sizeof(struct pqRep));  // make room for the structure
    if (q == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(0);
    }
    q->items = malloc((size+1) * sizeof(Edge)); // make room for the array
    if (q->items == NULL) {                // size+1 because heap 1..size
        fprintf(stderr, "out of memory\n");
        exit(0);
    }
    q->nItems = 0;                          // we have no items yet
    q->maxsize = size;                      // remember the maxsize
    return q;                               // return the initial PQ
}

// an Edge is inserted, not an int
void insertPQ(Edge e,PQ q) {
    if (q == NULL) {
        fprintf(stderr, "priority queue not initialised\n");
        exit(1);
    }
    if (q->nItems == q->maxsize) {
        fprintf(stderr, "priority queue full\n");
        exit(1);
    }
    q->nItems++;                    // adding another item
    q->items[q->nItems] = e;       // put the item at the end
    fixUp(q->items, q->nItems);     // fixUp all the way to the root
    return;
}

// 'min' not 'max plus returns Edge
Edge delMinPQ(PQ q) {
    if (q == NULL) {
        fprintf(stderr, "priority queue not initialised\n");
        exit(1);
    }
    if (q->nItems == 0) {
        fprintf(stderr, "priority queue empty\n");
        exit(1);
    }
    Edge retval = q->items[1];          // this is the item we want to return
    q->items[1] = q->items[q->nItems]; // overwrite root by last item
    q->nItems--;                       // we are decreasing heap size by 1
    fixDown(q->items, 1, q->nItems);   // fixDown the new root
    return retval;
}

int isEmptyPQ(PQ q) {
    int empty = 0;
    if (q == NULL) {
        fprintf(stderr, "isEmptyPQ: priority queue not initialised\n");
    }
    else {
        empty = q->nItems == 0;
    }
    return empty;
}

void showPQ(PQ q) {
    for(int i=0;i<q->nItems+1;i++)
    {
        printf("%d %d %5.2f\n",q->items[i].v, q->items[i].w, q->items[i].x);
    }
}