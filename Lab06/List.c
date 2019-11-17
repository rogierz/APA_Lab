//
// Created by Ruggero Nocera on 16/11/2019.
//

#include <stdlib.h>
#include <string.h>
#include "List.h"
#include "Item.h"

typedef struct node* link;

struct node{
    Item item;
    link next;
};

struct list{
    link head;
    int N;
};

static link newNode(Item val, link next){
    link tmp = malloc(sizeof(struct node));
    tmp->item = val;
    tmp->next = next;
    return tmp;
}
LIST LISTinit(){
    LIST tmp;
    tmp = malloc(sizeof(struct list*));
    tmp->head = NULL;
    tmp->N = 0;
    return tmp;
}

void LISTsortIns(LIST l, Item val){
    link x, p;
    if(l->head == NULL || ITEMcmp(l->head->item, val) > 0) {
        l->head = newNode(val, l->head);
        l->N++;
        return;
    }
    for(x = l->head->next, p = l->head; x != NULL && ITEMcmp(x->item, val) < 0; p = x, x = x->next);
    p->next = newNode(val, x);
    l->N++;
}

void LISTprint(LIST l, FILE *fp){
    link x;
    for(x = l->head; x != NULL; x = x->next){
        ITEMprint(x->item, fp);
    }
}

Item LISTsearch(LIST l, char *code){
    link x;
    for(x = l->head; x != NULL && strcmp(code, x->item.codice); x = x->next);
    if(x != NULL) return x->item;
    return ITEMnull();
}