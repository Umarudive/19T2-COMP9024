//
// Created by Wanchao Huang on 2019-07-03.
//
// quack.h: an interface definition for a queue/stack
#include <stdio.h>
#include <stdlib.h>

typedef struct node *Quack;

Quack createQuack(void);    // create and return Quack

void  push(int, Quack);     // put the given integer onto the quack

int   pop(Quack);           // pop and return the top element on the quack

int   isEmptyQuack(Quack);  // return 1 is Quack is empty, else 0

void  makeEmptyQuack(Quack);// remove all the elements on Quack

void  showQuack(Quack);     // print the contents of Quack, from the top down

void qush(int data, Quack que); // move each element up 1
