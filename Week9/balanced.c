// unbalanced.c: create and check the balance of a tree
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *Tree;
struct node {
    int data;
    Tree left;
    Tree right;
};

void printTree(Tree, int); // print a BST with indentation
Tree createTree(int);        // create a BST with root 'v'
Tree insertTree(Tree, int);// insert a node 'v' into a BST
void freeTree(Tree);       // give the memory back to the heap
Tree deleteTree(Tree t, int i);
Tree joinDLMD(Tree t1, Tree t2);
Tree joinDRMD(Tree t1, Tree t2);

int count(Tree);
int balance(Tree);
int height(Tree);

int main(void) {
    Tree t;

    printf("Input root: ");
    int root = getchar();
    t = createTree(root);

    char *str = malloc(1024);
    printf("Insert node: ");
    int node;
    while((scanf("%d",&node)==1))
    {
        t = insertTree(t, node);
    }

    printTree (t, 0);
    printf("Balance = %d\n", balance(t));
    printf("Height = %d\n", height(t));
    printf("Count = %d\n", count(t));

    getchar();
    printf("Delete node: ");
    int del_num;
    scanf("%d",&del_num);
    deleteTree(t,del_num);
    printTree(t,0);


    freeTree(t);
    return EXIT_SUCCESS;
}
void printTree(Tree t, int depth) {
    if (t != NULL) {
        depth++;
        printTree (t->left, depth);
        int i;
        for (i=1; i<depth; i++){
            putchar('\t');
        }
        printf ("%d\n", t->data);
        printTree (t->right, depth);
    }
    return;
}

Tree createTree (int v) {
    Tree t;
    t = malloc(sizeof(struct node));
    if (t == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    t->data = v;
    t->left = NULL;
    t->right = NULL;
    return t;
}

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

int count(Tree t){
    int countree = 0;
    if (t != NULL) {
        countree = 1 + count(t->left) + count(t->right);
    }
    return countree;
}

int max(int a, int b){
    if (a >= b){
        return a;
    }
    return b;
}

int height(Tree t){
    int heightree = -1;
    if (t != NULL){
        heightree = 1 + max(height(t->left), height(t->right));
    }
    return heightree;
}

int balance (Tree t){ // calculates the difference between left and right
    int diff = 0;

    if (t != NULL) {
        diff = count(t->left) - count(t->right);
        if (diff < 0) {
            diff = -diff;
        }
    }
    return diff;
}

// Joins t1 and t2 with the deepest left-most descendent of t2 as new root.
Tree joinDLMD(Tree t1, Tree t2){
    Tree nuroot;
    if (t1 == NULL) {         // actually should never happen
        nuroot = t2;
    }
    else if (t2 == NULL) {    // actually should never happen
        nuroot = t1;
    }
    else {                    // find the DLMD of the right subtree t2
        Tree p = NULL;
        nuroot = t2;
        while (nuroot->left != NULL) {
            p = nuroot;
            nuroot = nuroot->left;
        }                      // nuroot is the DLMD, p is its parent
        if (p != NULL){
            p->left = nuroot->right; // give nuroot's only child to p
            nuroot->right = t2;      // nuroot replaces deleted node
        }
        nuroot->left = t1;           // nuroot replaces deleted node
    }
    return nuroot;
}

// Joins t1 and t2 with the deepest right-most descendent of t2 as new root.
Tree joinDRMD(Tree t1, Tree t2){
    Tree nuroot;
    if (t2 == NULL) {         // actually should never happen
        nuroot = t1;
    }
    else if (t1 == NULL) {    // actually should never happen
        nuroot = t2;
    }
    else {                    // find the DRMD of the left subtree t2
        Tree p = NULL;
        nuroot = t1;
        while (nuroot->right != NULL) {
            p = nuroot;
            nuroot = nuroot->right;
        }                      // nuroot is the DRMD, p is its parent
        if (p != NULL){
            p->right = nuroot->left; // give nuroot's only child to p
            nuroot->left = t1;      // nuroot replaces deleted node
        }
        nuroot->right = t2;           // nuroot replaces deleted node
    }
    return nuroot;
}

Tree deleteTree(Tree t, int v){ // delete node with value 'v'
    if (t != NULL) {
        if (v < t->data) {
            t->left = deleteTree(t->left, v);
        }
        else if (v > t->data) {
            t->right = deleteTree(t->right, v);
        }
        else {                 // v == t->data, so the node 't' must be deleted
                               // next fragment of code violates style, just to make logic clear
            Tree n;            // temporary
            if (t->left==NULL && t->right==NULL)
                n=NULL;        // 0 children
            else if (t->left ==NULL)
                n=t->right;    // 1 child
            else if (t->right==NULL)
                n=t->left;     // 1 child
            else
                n=joinDLMD(t->left,t->right);
                //n=joinDRMD(t->left,t->right);
            free(t);
            t = n;
        }
    }
    return t;
}



void freeTree(Tree t) { // free in postfix fashion
    if (t != NULL) {
        freeTree(t->left);
        freeTree(t->right);
        free(t);
    }
    return;
}