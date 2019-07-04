/*
 * Write a C-program that outputs, in alphabetical order, all strings
 * that use each of the characters 'a', 'b', 'l', 'e' exactly once.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LEN 4

typedef struct Node
{
    char elements[5];
    struct Node *next;
}Node;



int main(void)
{
    //Node *start = NULL;

    int count =0;
    //char *word = malloc(LEN+1);

    char a[] ={'a','b','l','e'};
    char tmp[5];
    tmp[4]='\0';

    Node *l1;
    Node *head = NULL;
    Node *pre = NULL;

    for(int i = 0; i<LEN;i++)
    {
        for(int j = 0; j<LEN;j++)
        {
            for(int k = 0; k<LEN;k++)
            {
                for(int l = 0; l<LEN;l++)
                {
                    if(i!=j && i!=k && i!=l && j!=k && j!=l && k!=l)
                    {

                        tmp[0]=a[i];
                        tmp[1]=a[j];
                        tmp[2]=a[k];
                        tmp[3]=a[l];

                        //printf("%s\n",tmp);
                        if(count == 0){
                            l1 = malloc(sizeof(Node));
                            //l1->elements = malloc(sizeof(5));
                            strcpy(l1->elements, tmp);
                            l1->next = NULL;
                            head = l1;
                        }
                        else
                        {
                            l1 = malloc(sizeof(Node));
                            //l1->elements = malloc(sizeof(5));
                            strcpy(l1->elements, tmp);
                            l1->next = NULL;
                            pre -> next = l1;
                        }
                        pre = l1;
                        count++;
                    }
                }
            }
        }
    }


    Node *cur;
    Node *tail;

    cur = head;
    tail = NULL;

    //temp[4]='\0';
    while(cur!= tail)
    {
        while(cur->next != tail)
        {
            //printf("%s %s\n",cur->elements,cur->next->elements);
            //printf("%d\n",strcmp(cur->elements, cur->next->elements));
            if(strcmp(cur->elements, cur->next->elements) > 0)
            {
                char temp[5];

                strcpy(temp,cur->elements);
                //char temp=*(cur->elements);
                strcpy(cur->elements,cur->next->elements);
                //cur->elements = cur->next->elements;
                strcpy(cur->next->elements,temp);
                //cur->next->elements = temp;
            }
           cur=cur->next;
        }
        tail = cur;
        cur = head;
    }
    Node *start;
    for (start = head;start != NULL; start = start->next)
    {
        printf("%s\n",start->elements);
    }


    printf("%d\n",count);
    //free(word);
    //return EXIT_SUCCESS;
}