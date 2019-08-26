// basic.c: insert nodes into a BST, print the tree and free all nodes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node *Tree;
struct node {
    int data;
    Tree left;
    Tree right;
};

Tree insertTree (Tree, int);
Tree createTree (int);
void printTree  (Tree,int);
void freeTree   (Tree);
int sumTree(Tree);
Tree revTree(Tree);

int main(int argc, char **argv) {
    Tree t;

    if(argc ==1)
        return EXIT_SUCCESS;

    for(int i = 1; i<argc;i++)
    {
        int num;
        if(sscanf(argv[i],"%d",&num)==1)
        {
            t = insertTree(t,num);
        }
    }

    printTree(t,0);
    printf("Tree in reverse:\n");
    t = revTree(t);
    printTree(t,0);

    if(t!=NULL)
        printf("Sum = %d",sumTree(t));
    putchar('\n');

    freeTree(t);
    return EXIT_SUCCESS;
}

// insert by recursive
Tree insertTree(Tree t, int v) {
    if (t == NULL) {
        t = createTree(v);
    }
    else {
        if (v < t->data) {
            t->left = insertTree (t->left, v);
        }
        else {
            t->right = insertTree (t->right, v);
        }
    }
    return t;
}

// insert by iteratively
Tree insertTreeI(Tree t, int v) { // An iterative version of the above
    if (t == NULL) {
        t = createTree(v);
    }
    else { // t != NULL
        Tree parent = NULL;  // remember the parent to link in new child
        Tree step = t;
        while (step != NULL) { // this is the iteration
            parent = step;
            if (v < step->data) {
                step = step->left;
            }
            else {
                step = step->right;
            }
        } // step == NULL
        if (v < parent->data) {
            parent->left = createTree(v);
        }
        else {
            parent->right = createTree(v);
        }
    }
    return t;
}

Tree createTree (int v) {
    Tree t = NULL;

    t = malloc (sizeof(struct node));
    if (t == NULL) {
        fprintf(stderr, "Memory is exhausted: exiting\n");
        exit(1);
    }
    t->data = v;
    t->left = NULL;
    t->right = NULL;
    return t;
}

void printTree(Tree t,int depth) { // not the final version
    if(t!=NULL)
    {
        depth++;
        printTree(t->left,depth);
        for(int i = 0;i<depth;i++) {
            putchar('\t');
        }
        printf("%d\n",t->data);
        printTree(t->right,depth);
    }
    return;
}

void freeTree(Tree t) { // free in postfix fashion
    if (t != NULL) {
        freeTree(t->left);
        freeTree(t->right);
        free(t);
    }
    return;
}

int sumTree(Tree t)
{
    int sum = 0;
    if(t!=NULL)
    {
        sum = t->data + sumTree(t->left) + sumTree(t->right);
    }
    return sum;
}

Tree revTree(Tree t)
{
    Tree copy = NULL;
    if(t!=NULL)
    {
        copy = malloc(sizeof(struct node));
        if(copy == NULL)
        {
            printf("error");
        }
        copy -> data = t->data;
        copy->left = revTree(t->right);
        copy->right = revTree(t->left);
    }
    return copy;
}