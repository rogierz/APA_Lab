//
// Created by Ruggero Nocera on 28/11/2019.
//

#include "LISTPG.h"
#include "PG.h"
#include <stdlib.h>

struct nodoPg_t{
    PG pg;
    linkNodoPG next;
};

struct listaPg_t{
    linkNodoPG head;
    linkNodoPG tail;
    int nPg;
};

LISTPG LISTPGinit(){
    LISTPG ret = malloc(sizeof(struct listaPg_t));
    ret->head = ret->tail = NULL;
    ret->nPg = 0;
    return ret;
}

linkNodoPG PGnewNode(PG pg, linkNodoPG next){
    linkNodoPG ret = malloc(sizeof(struct nodoPg_t));
    ret->pg = pg;
    ret->next = next;
    return ret;
}

void PGfreeNode(linkNodoPG link){
    PGfree(link->pg);
    free(link);
}

void LISTPGSortedIns(LISTPG list, PG pg){
    linkNodoPG x, p;
    list->nPg++;
    if(list->head == NULL || PGcmp(pg, list->head->pg) < 0){
        list->head = PGnewNode(pg, list->head);
        if(list->head->next == NULL) list->tail = list->head;
        return;
    }

    for(x = list->head->next, p = list->head; x != NULL && PGcmp(pg, x->pg) >= 0; p = x, x = x->next);
    p->next = PGnewNode(pg, x);
    if(x == NULL) list->tail = p;
    return ;
}

void LISTPGdelete(LISTPG list, char* code){
    linkNodoPG x, p;
    if(list->head == NULL) return;
    if(PGcmpCode(list->head->pg, code) == 0){
        x = list->head;
        list->head = list->head->next;
        if(list->tail == x) list->tail = list->tail->next;
        PGfreeNode(x);
        list->nPg--;
    }

    for(x = list->head->next, p = list->head; x != NULL && PGcmpCode(x->pg, code) != 0; p = x, x = x->next);
    if(x == NULL) return;
    p->next = x->next;
    if(p->next == NULL) list->tail = p;
    PGfreeNode(x);
    list->nPg--;
}

PG LISTPGsearch(LISTPG list, char* code){
    if(list == NULL) return PGnull();
    linkNodoPG x;
    for(x = list->head; x != NULL && PGcmpCode(x->pg, code) != 0; x = x->next);
    if(x != NULL) return x->pg;
    return PGnull();
}

void LISTPGprint(LISTPG list, FILE *fp){
    linkNodoPG x;
    for(x = list->head; x != NULL; x = x->next){
        PGprint(x->pg, fp);
    }
}

void LISTPGfree(LISTPG list){
    linkNodoPG x, p;
    for(x = list->head->next, p = list->head; x != NULL; p = x, x = x->next){
        PGfreeNode(p);
    }
    PGfreeNode(list->tail);
    free(list);
}