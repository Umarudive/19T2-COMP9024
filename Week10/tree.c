#include "tree.h"



Tree rotateLeft(Tree t) { // Rotate left code: includes count field
    Tree retval = NULL;
    if (t != NULL) {
        Tree nuroot = t->right;    // left rotate: hence right root-child will become new root
        if (nuroot == NULL) {
            retval = t;
        }
        else {
            t->right = nuroot->left;  // the left child of nuroot becomes old root's right child
            nuroot->left = t;         // nuroot's left child is the old root
            nuroot->count = t->count; // nuroot and old root have the same count
            t->count = 1 + sizeTree(t->left) + sizeTree(t->right); // recompute count in old root
            retval = nuroot;          // return with the new root
        }
    }
    return retval;
}

Tree rotateRight(Tree t) { // Rotate right code: includes count field
    Tree retval = NULL;
    if (t != NULL) {
        Tree nuroot = t->left;
        if (nuroot == NULL) {
            retval = t;
        }
        else {
            t->left = nuroot->right;
            nuroot->right = t;
            nuroot->count = t->count;
            t->count = 1 + sizeTree(t->left) + sizeTree(t->right);
            retval = nuroot;
        }
    }
    return retval;
}

Tree balance(Tree t) {
    Tree retval = NULL;
    if (t != NULL) {
        if (t->count <= 1){
            retval = t;
        }
        else {
            t = partition(t, t->count/2);
            t->left = balance(t->left);
            t->right = balance(t->right);
            retval = t;
        }
    }
    return retval;
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

Tree createTree(int v) {
    Tree t = malloc (sizeof(struct node));
    if (t == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    t->data = v;
    t->left = NULL;
    t->right = NULL;
    t->count = 1;
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
        t->count++;    // update the counter at each ancestor
    }
    return t;
}

int sizeTree(Tree t)
{
    int retval = 0;
    if(t!=NULL)
    {
        retval = t->count;
    }
    return retval;
}

// For tree with n nodes – indexes are 0..n-1
int selectTree(Tree t, int i) { // for tree with n nodes - indexed from 0..n-1
    int retval = 0;
    if (t != NULL) {
        int numOnLeft = 0;             // this is if there is no left branch
        if (t->left != NULL) {
            numOnLeft = t->left->count; // this is if there is a left branch
        }
        if (numOnLeft > i) {           // left subtree or ...
            retval = selectTree(t->left, i);
        }
        else if (numOnLeft < i) {      // ... right subtree ?
            retval = selectTree(t->right, i-(numOnLeft+1));
        }
        else {
            retval = t->data;          // value index i == numOnLeft
        }
    }
    else {
        printf("Index does not exist\n");
        retval = 0;
    }
    return retval;
}

Tree partition(Tree t, int i) { // make node at index i the root
    Tree retval = NULL;
    if (t != NULL) {
        int numOnLeft = 0;
        if (t->left != NULL) {
            numOnLeft = t->left->count;
        }
        if (numOnLeft > i) {
            t->left = partition(t->left, i);
            t = rotateRight(t);
        }
        if (numOnLeft < i) {
            t->right = partition(t->right, i-(numOnLeft+1));
            t = rotateLeft(t);
        }
        retval = t;
    }
    else {
        printf("Index does not exist\n");
        retval = NULL;
    }
    return retval;
}

void freeTree(Tree t) { // free in postfix fashion
    if (t != NULL) {
        freeTree(t->left);
        freeTree(t->right);
        free(t);
    }
    return;
}

Tree splayInsertion(Tree t, int it){
// multiple return here ONLY because I need the room for comments on the right
    // if it == null
    if (it == -1){
        return t;
    }
    if (t == NULL){
        return createTree(it);
    }

    Tree it1 = createTree(it);
    if (it1->data < t->data) {
        if (t->left == NULL) {
            // ZIG
            t->left = createTree(it);     // make a new link for this element
            t->count++;                  // increment the count at parent
            return rotateRight(t);        // rotate parent
        }
        if (it1->data < t->left->data) {  // it < gparent & it < lparent
            // ZIGZIG
            t->left->left = splayInsertion(t->left->left, it);
            t->left->count++;            // incr lparent
            t->count++;                  // incr gparent
            t = rotateRight(t);           // ZIG: rotate gparent
        } else {                         // it < gparent & it >= lparent
            // ZIGZAG
            t->left->right = splayInsertion(t->left->right, it);
            t->left->count++;            // incr lparent
            t->count++;                  // incr gparent
            t->left = rotateLeft(t->left);// ZAG: rotate lparent
        }
        return rotateRight(t);           // ZIG: rotate gparent
    } else {
        if (t->right == NULL) {
            // ZIG
            t->right = createTree(it);   // analogous to the left case above
            t->count++;
            return rotateLeft(t);
        }
        if (it1->data < t->right->data){ // it > gparent & it < rparent
            // ZIGZAG
            t->right->left = splayInsertion(t->right->left, it);
            t->right->count++;          // incr rparent
            t->count++;                 // incr gparent
            t->right = rotateRight(t->right); // ZAG: rotate rparent
        } else {                        // it > gparent & it >= rparent
            // ZIGZIG
            t->right->right = splayInsertion(t->right->right, it);
            t->right->count++;          // incr rparent
            t->count++;                 // incr gparent
            t = rotateLeft(t);           // ZIG: rotate gparent
        }
        return rotateLeft(t);           // ZIG: rotate gparent
    }
}