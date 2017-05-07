#ifndef LIST_H
#define LIST_H

typedef struct listitem{
    unsigned int v; //if guard, v contains parent object id
    unsigned short isGuard; // 0 | 1
    struct listitem *next;
    struct listitem *prev;
} ListItem;

typedef struct list{
    ListItem *start;
    ListItem *end;
} List;

extern List *initList(unsigned int parentId);
extern void appendToList(unsigned int i, List *l);
extern void mergeListAfterItem(List **ins, ListItem *item);
extern List *splitListAfterItem(List *l, ListItem *item, unsigned int parentId);
extern void clearList(List **l);
extern void removeItemFromList(ListItem *li);

#endif /* LIST_H */
