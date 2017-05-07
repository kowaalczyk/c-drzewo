#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "tree.h"

#define MEM_ERROR_CODE 2
#define MAX_GRAPH_SIZE 200000

Node *newNode(unsigned int id, ListItem *parentListPos) {
    Node *n = (Node*)malloc(sizeof(Node));
    n->children = initList(id);
    n->id = id;
    n->parentListPos = parentListPos;
    return n;
}

Graph *initGraph() {
    Graph *g = (Graph*)malloc(sizeof(Graph));
    Node *n = newNode(0, NULL);
    g->start = n;
    g->allocNodes = 1;
    g->nodes = 1;
    g->maxNodes = 1;

    Node **tmp = (Node**)malloc(MAX_GRAPH_SIZE * sizeof(Node*));
    if(tmp) {
        g->ptr = tmp;
        g->maxNodes += MAX_GRAPH_SIZE;
        g->ptr[0] = n;
    } else {
        printf("%s", "malloc failed");
        exit(MEM_ERROR_CODE);
    }
    return g;
}

void resizeGraph(Graph *g) {
    Node **tmp = (Node**)realloc((g->ptr), sizeof(Node*)*((g->maxNodes)+1000));
    if(tmp) {
        g->ptr = tmp;
        g->maxNodes += 1000;
    } else {
        printf("%s", "realloc failed");
        exit(MEM_ERROR_CODE);
    }
}

void addNode(unsigned int id, unsigned int parentId, Graph *g) {
    Node *parent = g->ptr[parentId];
    (g->allocNodes)++;
    (g->nodes)++;
    if(g->allocNodes >= g->maxNodes) {
        //Realloc memory if necessary
        resizeGraph(g);
    }

    appendToList(id, parent->children);
    Node *n = newNode(id, parent->children->end->prev);
    g->ptr[id] = n;
}

long int rightChild(unsigned int id, Graph g) {
    Node *n = g.ptr[id];
    if(n->children->end->prev->isGuard) {
      return -1;
    } else {
      return n->children->end->prev->v;
    }
}

void clearNode(Node **n, Graph *g) {
  if(*n) {
    unsigned int id = (*n)->id;
    g->ptr[id] = NULL;
    removeItemFromList((*n)->parentListPos);
    clearList(&((*n)->children));
    free(*n);
    *n = NULL;
    (g->nodes)--;
  }
}

void deleteNode(unsigned int id, Graph *g) {
    Node *n = g->ptr[id];
    mergeListAfterItem(&(n->children), n->parentListPos);
    clearNode(&n, g);
}

void deleteSubtree(unsigned int id, Graph *g) {
    Node *subtree = g->ptr[id];
    if(subtree) {
        ListItem *child = subtree->children->start->next;
        while(child && child->isGuard == 0) {
            unsigned int childId = child->v;
            child = child->next;
            deleteSubtree(childId, g);
        }
        clearNode(&subtree, g);
    }
}

void setNodeChildrenList(Node *n, List *l) {
    clearList(&(n->children));
    n->children = l;
}

void splitNode(unsigned int id, unsigned int parentId, unsigned int parentPosId, Graph *g) {
    ListItem *targetListPos = g->ptr[parentPosId]->parentListPos;
    List *newNodeChildren = splitListAfterItem(g->ptr[parentId]->children, targetListPos, parentId);

    addNode(id, parentId, g);
    Node *n = g->ptr[id];
    setNodeChildrenList(n, newNodeChildren);
}

void clearGraph(Graph *g) {
  deleteSubtree(0, g);
  free(g->ptr);
  free(g);
}
