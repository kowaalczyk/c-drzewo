#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tree.h"

#define ARG_ERROR_CODE 1

int main(int argc, char *args[]) {
    //declarations
    char cmd[20];
    unsigned int param1, param2;
    unsigned int lastCreatedNodeNumber;
    unsigned short printNodesNumber;
    Graph *g = initGraph();
    lastCreatedNodeNumber = 0;
    printNodesNumber = 0;

    //handle program parameters
    for(int i=1; i<argc; i++) {
      if(i==1 && strcmp(args[i], "-v")==0) {
        printNodesNumber = 1;
      } else {
        // too much or wrong parameters
        printf("ERROR\n");
        exit(ARG_ERROR_CODE);
      }
    }

    while(scanf("%s", cmd)!=EOF) {
        if(!strcmp(cmd, "ADD_NODE")) {
            scanf("%u", &param1);
            addNode(++lastCreatedNodeNumber, param1, g);
            printf("%s\n", "OK");
        }
        else if(!strcmp(cmd, "RIGHTMOST_CHILD")) {
            scanf("%u", &param1);
            printf("%li\n", rightChild(param1, *g));
        }
        else if(!strcmp(cmd, "DELETE_NODE")) {
            scanf("%u", &param1);
            deleteNode(param1, g);
            printf("%s\n", "OK");
        }
        else if(!strcmp(cmd, "DELETE_SUBTREE")) {
            scanf("%u", &param1);
            deleteSubtree(param1, g);
            printf("%s\n", "OK");
        }
        else if(!strcmp(cmd, "SPLIT_NODE")) {
            scanf("%u", &param1);
            scanf("%u", &param2);
            splitNode(++lastCreatedNodeNumber, param1,param2, g);
            printf("%s\n", "OK");
        }
        else {
            /* command not supported */
            break;
        }
        
        if(printNodesNumber) {
          fprintf(stderr, "%s%u\n", "NODES: ", g->nodes);
        }
    }
    clearGraph(g);

    return 0;
}
