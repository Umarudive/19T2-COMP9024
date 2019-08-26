#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *Tree;
struct node {
    int data;
    Tree left;
    Tree right;
    int count;
};


void printTree(Tree, int); // print a BST with indentation
Tree createTree(int);        // create a BST with root 'v
int sizeTree(Tree t);
Tree insertTree(Tree, int);// insert a node 'v' into a BST
void freeTree(Tree);       // give the memory back to the heap
Tree partition(Tree, int);

Tree rotateLeft(Tree t);
Tree rotateRight(Tree t);
Tree balance(Tree t);
int selectTree(Tree, int);
Tree splayInsertion(Tree, int);
