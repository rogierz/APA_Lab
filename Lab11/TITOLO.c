//
// Created by Ruggero Nocera on 11/01/2020.
//

#include "TITOLO.h"
#include "QUOT.h"
#include <stdlib.h>
#include <string.h>

struct titolo_s{
    char *nome;
    float min, max;
    BSTQUOT quotazioni;
};

typedef struct nodoListTitoli_s * link;
struct nodoListTitoli_s{
    TITOLO t;
    link next;
};

struct listTitoli_s{
    link head;
    link z;
    int N;
};

static link NEWnode(TITOLO t, link next){
    link x = malloc(sizeof(struct nodoListTitoli_s));
    x->t = t;
    x->next = next;
    return x;
}
TITOLO TITOLOnew(char *nome){
    TITOLO t = malloc(sizeof(struct titolo_s));
    t->nome = strdup(nome);
    t->min = t->max = -1.0;
    t->quotazioni = BSTQUOTinit();
    return t;
}
void TITOLOfree(TITOLO t){
    BSTQUOTfree(t->quotazioni);
    free(t->nome);
    free(t);
}
char * TITOLOgetKey(TITOLO t){
    return strdup(t->nome);
}

void TITOLOaddTransazione(TITOLO t, DATA d, float val, int qta){
    BSTQUOTinsert(t->quotazioni, d, val, qta);
    BSTQUOTminmax(t->quotazioni, &(t->min), &(t->max));
}
void TITOLOstore(TITOLO t, FILE *fp){
    fprintf(fp, "%s\n", t->nome);
    BSTQUOTstore(t->quotazioni, fp);
}

QUOT TITOLOsearchQuot(TITOLO t, DATA d){
    return BSTQUOTsearch(t->quotazioni, d);
}

void TITOLOminMaxRange(TITOLO t, DATA d1, DATA d2, float *min, float *max){
    BSTQUOTminMaxRange(t->quotazioni, d1, d2, min, max);
}

void TITOLOminmax(TITOLO t, float *min, float *max){
    *min = t->min;
    *max = t->max;
}

float TITOLObstRatio(TITOLO t){
    return BSTQUOTmaxHeight(t->quotazioni)/(float)BSTQUOTminHeight(t->quotazioni);
}
void TITOLObalanceBst(TITOLO t){
    BSTQUOTbalance(t->quotazioni);
}
LISTtitoli LISTinit(){
    LISTtitoli l = malloc(sizeof(struct listTitoli_s));
    l->z = NEWnode(NULL, NULL);
    l->head = l->z;
    l->N = 0;
    return l;
}

void LISTaddTitolo(LISTtitoli l, TITOLO t){
    if(t == NULL) return;
    l->head = NEWnode(t, l->head);
    l->N++;
}

TITOLO LISTsearchTitolo(LISTtitoli l, char *cod){
    link x;
    for(x = l->head; x != l->z && strcmp(TITOLOgetKey(x->t), cod) != 0; x=x->next);
    if(x != l->z)
        return x->t;
    return NULL;
}
static void storeR(link h, link z, FILE *fp){
    if(h == z)
        return;
    TITOLOstore(h->t, fp);
    storeR(h->next, z, fp);
}
void LISTstore(LISTtitoli l, FILE *fp){
    storeR(l->head, l->z, fp);
}
void LISTfree(LISTtitoli l){
    link x, y;
    for(x = l->head; x != NULL; x = y){
        y = x->next;
        TITOLOfree(x->t);
        free(x);
    }
    free(l);
}