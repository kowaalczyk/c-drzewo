#ifndef TREE_H
#define TREE_H

#include "list.h"

typedef struct node {
    unsigned int id;
    unsigned int parentId;
    ListItem *parentListPos;
    List *children;
} Node;

typedef struct graph {
    unsigned int maxNodes;
    unsigned int allocNodes; //including start node
    unsigned int nodes;
    Node *start;
    Node **ptr; /* array of pointers to nodes */
} Graph;

extern Graph* initGraph();
extern void addNode(unsigned int id, unsigned int parentId, Graph *g);
extern long int rightChild(unsigned int id, Graph g);
extern void deleteNode(unsigned int id, Graph *g);
extern void deleteSubtree(unsigned int id, Graph *g);
extern void splitNode(unsigned int id, unsigned int parentId, unsigned int parentPosId, Graph *g);
extern void clearGraph(Graph *g);

#endif /* TREE_H */
