// unbalanced.c: create and check the balance of a tree
#include "tree.h"
#include <unistd.h>

int main(void) {

    printf("Welcome my master\n"
           "To start, insert a root node so that i can build the tree for u\n");
    // build tree
    printf("Your root: ");
    Tree t;
    char temp[5];
    fgets(temp, sizeof(int),stdin);
    int root = atoi(temp);
    t = createTree(root);
    printf("Now insert your tree node: ");
    char *str = malloc(1024);
    fgets(str,1024,stdin);

    char *w = strtok(str," ");
    while(w)
    {
        t = insertTree(t, atoi(w));
        w = strtok(NULL, " ");
    }
    printf("------------------------------\n");

    printf("\t\tBuilding.     1%%\n");
    sleep(1);
    printf("\t\tBuilding..    50%%\n");
    sleep(1);
    printf("\t\tBuilding...   99%%\n");
    sleep(1);


    printf("Mission Complete! Here is your tree: \n");
    printTree (t, 0);
    printf("------------------------------\n");
    printf("You can try other functions here, my master.\n");
    printf("Input function number as listed: \n");
    printf("\t1 for rotate tree\n");
    printf("\t2 for select node in tree\n");
    printf("\t3 for partition\n");
    printf("\t4 for balance tree\n");
    printf("\t5 for splay insertion\n");
    putchar('\n');
    printf("\tOthers for Goodnight\n");

    printf("Make your choice: ");
    char fun[5];
    fgets(fun, sizeof(int),stdin);
    int f_num = atoi(fun);

    switch(f_num)
    {
        case 1:
            printf("------------------------------\n");
            // rotate tree
            printf("Here you can rotate the tree: \n");

            printf("\tInput 'r' for right rortate\n");
            printf("\tInput 'l' for left rortate\n");
            printf("Which direction?\n");
            char dir = getchar();
            if(dir =='r')
            {
                printf("Right rotation complete!\n");
                t = rotateRight(t);
            }
            else if(dir == 'l')
            {
                printf("Left rotation complete!\n");
                t = rotateLeft(t);
            }
            printTree(t,0);
            break;

        case 2:
            printf("------------------------------\n");
            // select the node from heap and print the node
            printf("Select Node index: ");
            char num1[5];
            fgets(num1, sizeof(int),stdin);
            int insert_num1 = atoi(num1);
            int selected1 = selectTree(t,insert_num1);
            if(selected1!=0)
            {
                printf("You have selected: %d\n",selected1);
            }
            break;

        case 3:
            printf("------------------------------\n");
            // use partition to select node
            // partition means select a node as a new root and rebuild the tree
            printf("Select Node index for partition: ");
            char num2[5];
            fgets(num2, sizeof(int),stdin);
            int insert_num2 = atoi(num2);
            Tree p_new = partition(t,insert_num2);
            printf("\t\tBuilding ...\n");
            sleep(1);
            printf("Here is your new tree, my master\n");
            printTree(p_new,0);
            break;

        case 4:
            printf("------------------------------\n");
            // Move the median node to the root by partitioning on i = count/2
            printf("Here is your tree after balance, my master\n");
            Tree p_ban = balance(t);
            printTree(p_ban,0);
            break;


        case 5:
        {
            printf("------------------------------\n");
            printf("Insert node for splay insertion: ");

            char temp_roo[5];
            fgets(temp_roo,sizeof(int),stdin);
            int root_in = atoi(temp_roo);
            Tree splay_In = splayInsertion(t,root_in);

            printf("\t\tBuilding ...\n");
            sleep(1);
            printf("Here is your new tree, my master\n");
            printTree(splay_In,0);

            break;
        }

        default:
            break;
    }
    printf("------------------------------\n");

    printf("Goodnight, my master.\n");

    printf("------------------------------\n");


    free(str);
    freeTree(t);
    return EXIT_SUCCESS;
}



