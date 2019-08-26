#include <stdio.h>
#include <string.h>

int main()
{
    int array[10];
    //int array[10] = {0};
    //memset(array,-1, sizeof(array));
    for(int i=0;i<10;i++)
        printf("%d ",array[i]);
    putchar('\n');
}