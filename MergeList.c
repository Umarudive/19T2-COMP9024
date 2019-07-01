//
// Created by Wanchao Huang on 2019-06-29.
//

/*
 *  整合list a b 的元素
 *  a 123
 *  b 234
 *  合并后1234
 *  scanf
 */

#include <stdio.h>
#include <stdlib.h>

#define M 1024

typedef struct Node
{
    char elements;
    struct Node *next;
}Node;

Node *insert_data(Node *head);
Node *merge(Node *l1,Node *l2);
Node *dup(Node *l);
void *sortlist(Node *l);

Node *insert_data(Node *head)
{
    // get elements
    char *line = NULL;
    line = malloc(sizeof(Node));
    if(line == NULL)
    {
        fprintf(stderr,"Error\n");
        exit(EXIT_FAILURE) ;
    }
    scanf("%s",line);

    Node *l;
    Node *first = NULL;
    Node *previous = NULL;

    for ( char *w = line; *w !='\0'; w++ )
    {

        l = malloc(M);
        if(l == NULL)
        {
            fprintf(stderr,"Error\n");
            exit(EXIT_FAILURE) ;
        }

        l -> elements = *w;
        l -> next = NULL;

        if(w == line)
        {
            first = l;      // start node
        }
        else
        {
            previous -> next = l;
        }
        previous = l;

    }

    head = first;
    free(line);

    return head;

}


Node *merge(Node *l1,Node *l2)
{
    Node *head3 = NULL;
    Node *l3;
    Node *first=NULL;

    // smaller first
    if ((l1->elements == l2->elements)||(l1->elements < l2->elements))
    {
        first = l1;
        while (l1->next != NULL)
        {
            l3 = malloc(M);
            l3 -> next = l1;
            l1 = l1->next;
        }
    }
    else
    {
        first = l2;
        while (l2->next != NULL)
        {
            l3 = malloc(M);
            l3 -> next = l2;
            l2 = l2->next;
        }
    }

    if(l1->next == NULL)
    {
        l3 = l1;
        l3 ->next = l2;
    }
    else
    {
        l3 = l2;
        l3 ->next = l1;
    }

    head3=first;
    return head3;
}

Node *dup(Node *l)
{
    //Node *start;

    Node *p1;
    Node *p2;
    Node *dup;
    p1 = l;

    while (p1 != NULL && p1->next != NULL)
    {
        p2 = p1;

        while (p2->next != NULL)
        {
            if (p1->elements == p2->next->elements)
            {
                dup = p2->next;
                p2->next = p2->next->next;
                //free(dup);
            }
            else
            {
                p2 = p2->next;
            }
        }
        p1 = p1->next;
    }

    return l;
}

// Bubble sort
// repeatedly swapping the adjacent elements if they are in wrong order
void *sortlist(Node *l)
{
    Node *cur;
    Node *tail;

    cur = l;
    tail = NULL;

    while(cur != tail)
    {
        while(cur->next != tail)
        {
            // if wrong
            if(cur->elements > cur->next->elements)
            {
                // exchange elements
                char temp=cur->elements;
                cur->elements = cur->next->elements;
                cur->next->elements = temp;
            }
            cur = cur->next;
        }
        tail = cur;
        cur = l;
    }

    Node *start;
    for (start = l; start != NULL; start = start->next)
    {
        printf(" %c ", start->elements);
    }
    putchar('\n');
    exit(EXIT_SUCCESS);

}

int main(void)
{

    Node *head1 = NULL;
    Node *head2 = NULL;

    printf("First list: ");
    Node * l1 = insert_data(head1);

    printf("Second list: ");
    Node * l2 = insert_data(head2);
    putchar('\n');

    printf("Merged list: \n");
    Node * l3 = merge(l1,l2);

    //dup(l3);

    sortlist(dup(l3));

    free(l1);
    free(l2);
    free(l3);

}
