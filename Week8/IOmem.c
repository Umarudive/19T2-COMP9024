#include "IOmem.h"
#include "Graph.h"
#include <string.h>



int readNumV()
{
    char *temp = malloc(100 * sizeof(char));
    if(temp == NULL)
    {
        printf("Temp malloc failed.\n");
        exit(EXIT_FAILURE);
    }
    memset(temp, -1, 100);

    fgets(temp, sizeof(int), stdin);

    char numtemp[100];
    int num =0;
    int i=0;
    while(*temp != -1)
    {
        if(*temp != '#')
            numtemp[i++] = *temp;
        temp++;
    }
    num = atoi(numtemp);
    return num;
}

int readBuildGraph(Graph g)  // read int pairs from stdin
{
    char *temp = malloc(1024 * sizeof(char));
    if(temp == NULL)
    {
        printf("Temp malloc failed.\n");
        exit(EXIT_FAILURE);
    }
    memset(temp, -1, 1024);
    int time = 0;

    while(fgets(temp, 1024, stdin)!=NULL)
    {
        int if_odd = 0;
        int x=0;
        int y=0;
        int temp_num = 0;
        char *w = strtok(temp," ");
        while(w!=NULL)
        {
            temp_num = atoi(w);

            if(if_odd ==0)
            {
                x=temp_num;
                if_odd++;
            }
            else if (if_odd ==1)
            {
                y = temp_num;
                insertE(g,newEdge(x,y));
                if_odd = 0;
            }
            w = strtok(NULL," ");
        }
    }
    return 1;
}


int* mallocArray(int nV)       // malloc an array of length int * sizeof(int)
{
    int *p = malloc((nV+1) * sizeof(int));
    if(p == NULL)
    {
        printf("Malloc failed.\n");
        exit(EXIT_FAILURE);
    }

    for(int i=0;i<nV;i++)
    {
        *(p+i)=-1;
    }
    return p;
}

void printArray(char * str, int *array, int nV) // print an int array of length int
{
    printf("%s: {",str);
    for (int i =0;i<nV; i++)
    {
        if(i != nV-1)
            printf("%d, ",*(array + i));
        else
            printf("%d",*(array+i));
    }
    printf("}\n");
}
