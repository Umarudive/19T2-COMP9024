//
// Created by Wanchao Huang on 2019-07-03.
//

#include "quack.h"

#define HEIGHT 1000


struct node{
    int array[HEIGHT]; // value
    int top;  // index
};


Quack createQuack(void)
{
    Quack qs;
    qs = malloc(sizeof(struct node));
    if(qs == NULL)
    {
        exit(1);
    }
    qs -> top = -1;
    return qs;
}

void push(int data, Quack qs){
    if(qs == NULL)
    {
        fprintf(stderr,"error");
    }
    else
    {
        if(qs -> top >= HEIGHT -1)
        {
            fprintf(stderr,"error");
        }
        else
        {
            ++qs -> top;
            qs -> array[qs->top] = data;
        }
    }
    return;
}

int pop(Quack qs)
{
    int val=0;
    if(qs == NULL)
    {
        fprintf(stderr,"error");
    }
    else
    {
        if(isEmptyQuack(qs))
        {
            fprintf(stderr,"error");
        }
        else
        {
            val = qs -> array[qs -> top];
            --qs->top;
        }
    }
    return val;
}

int isEmptyQuack(Quack qs) {
    int empty = 0;
    if (qs == NULL) {
        fprintf(stderr, "isEmptyQuack: quack not initialised\n");
    }
    else {
        empty = qs->top < 0;
    }
    return empty;
}

void showQuack(Quack qs) {
    if (qs == NULL) {
        fprintf(stderr, "showQuack: quack not initialised\n");
    }
    else {
        printf("Quack: ");
        if (qs->top < 0) {
            printf("<< >>\n");
        }
        else {
            int i;
            printf("<<");                    // start with a <<
            for(i = qs->top;i>0;--i)
            {
                printf("%d", qs -> array[i]);
            }
            printf("%d>>\n", qs->array[0]);   // last element includes a >>
        }
    }
    return;
}


void qush(int data, Quack que)
{
    if(que == NULL)
    {
        fprintf(stderr,"quack not initialised\n");
        return;
    }
    if (que->top == HEIGHT-1)
    {
        fprintf(stderr,"quack overflow\n");
        return;
    }

    ++que->top;     // next available sort
    int i;

    for(i = que -> top; i >= 1; i--)
    {
        que -> array[i] = que -> array[i-1];       // move each element up 1
    }
    que -> array[0] = data;     // place new data at the bottom
    return;
}

void makeEmptyQuack(Quack qs) {
    if (qs == NULL) {
        fprintf(stderr, "makeEmptyQuack: quack not initialised\n");
    }
    else {
        while (!isEmptyQuack(qs)) {
            pop(qs);
        }
    }
    return;
}
