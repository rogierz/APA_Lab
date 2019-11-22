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

static void freeNode(link node){
    free(node);
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

Item LISTdeleteByCode(LIST l, char *code){
    link x, p;
    Item ret;
    if(ITEMcmpCode(l->head->item, code) == 0){
        x = l->head;
        l->head = l->head->next;
        ret = x->item;
        free(x);
        return ret;
    }
    for(x = l->head->next, p = l->head; x != NULL && ITEMcmpCode(x->item, code) != 0; p = x, x = x->next);
    if(x == NULL) return ITEMnull();
    ret = x->item;
    p->next = x->next;
    freeNode(x);
    return ret;
}

Item LISTdeleteFirstByDate(LIST l, data dataL, data dataR){
    link x, p;
    Item ret;
    int d1, d2;
    d1 = dataL.dataToInt;
    d2 = dataR.dataToInt;

    if(l->head == NULL) return ITEMnull();

    if(l->head->item.nascita.dataToInt <= d2 && l->head->item.nascita.dataToInt >= d1){
        ret = l->head->item;
        x = l->head;
        l->head = l->head->next;
        freeNode(x);
        return ret;
    }

    for(x = l->head->next, p = l->head; x != NULL && x->item.nascita.dataToInt <= d2 && x->item.nascita.dataToInt >= d1; p = x, x = x->next);
    if(x == NULL) return ITEMnull();
    ret = x->item;
    p->next = x->next;
    freeNode(x);
    return ret;
}