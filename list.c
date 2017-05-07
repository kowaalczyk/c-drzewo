#include <stdio.h>
#include <stdlib.h>
#include "list.h"

ListItem *initListItem(unsigned int i, unsigned short isGuard, ListItem *prev, ListItem *next) {
    ListItem *n = (ListItem*)malloc(sizeof(ListItem));
    n->v = i;
    n->isGuard = isGuard;
    n->next = next;
    n->prev = prev;
    return n;
}

List *initList(unsigned int parentId) {
    List *n = (List*)malloc(sizeof(List));
    n->start = initListItem(parentId, 1, NULL, NULL);
    n->end = initListItem(parentId, 1, NULL, NULL);
    n->start->next = n->end;
    n->end->prev = n->start;
    return n;
}

void appendToList(unsigned int i, List *l) {
    //assuming l is initialized
    ListItem *n = initListItem(i, 0, l->end->prev, l->end);
    n->prev->next = n;
    l->end->prev = n;
}

void clearList(List **l) {
    if(*l) {
        ListItem *li = (*l)->start;
        while(li) {
            ListItem *tmp = li;
            li = li->next;
            free(tmp);
        }
        free(*l);
        *l = NULL;
    }
}

void mergeListAfterItem(List **ins, ListItem *item) {
    //assuming the item exists on some list
    ListItem *tmp = item->next;
    if((*ins)->start->next != (*ins)->end) {
      item->next = (*ins)->start->next;
      (*ins)->start->next->prev = item;
      (*ins)->end->prev->next = tmp;
      tmp->prev = (*ins)->end->prev;
    } else {
      /* list ins is empty */
    }
    //dereferencing items moved from ins in order to clear the List
    (*ins)->start->next = (*ins)->end;
    (*ins)->end->prev = (*ins)->start;
    clearList(ins);
}

List *splitListAfterItem(List *l, ListItem *item, unsigned int parentId) {
    //assuming item is a valid ListItem of l
    List *newList = initList(parentId);
    ListItem *firstNotGuard = item->next;
    if(firstNotGuard->isGuard) {
      // splitting after last element ==> return empty list
    } else {
      ListItem *lastNotGuard = l->end->prev;
      newList->start->next = firstNotGuard;
      firstNotGuard->prev = newList->start;
      newList->end->prev = lastNotGuard;
      lastNotGuard->next = newList->end;
      item->next = l->end;
      l->end->prev = item;
    }
    return newList;
}

void removeItemFromList(ListItem *li) {
  if(li && li->isGuard == 0) {
    li->prev->next = li->next;
    li->next->prev = li->prev;
    free(li);
    li = NULL;
  }
}
