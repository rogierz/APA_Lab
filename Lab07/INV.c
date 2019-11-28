//
// Created by Ruggero Nocera on 28/11/2019.
//

#include "INV.h"
#include "PG.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct tabInv_t{
    INV* vettinv;
    int nInv;
    int maxInv;
};

struct inv_t{
    char nome[MAXNAME];
    char tipo[MAXNAME];
    struct stat_t stat;
};

INV INVscan(char *inv){
    INV ret = malloc(sizeof(struct inv_t));
    sscanf(inv, "%s %s %d %d %d %d %d %d", ret->nome, ret->tipo, &(ret->stat.hp), &(ret->stat.mp), &(ret->stat.atk), &(ret->stat.def),
           &(ret->stat.mag), &(ret->stat.spr));
    return ret;
}

struct stat_t INVgetStat(INV inv){
    return inv->stat;
}

TABINV TABINVinit(int maxN){
    TABINV ret = malloc(sizeof(struct tabInv_t));
    if(ret == NULL) return NULL;
    ret->maxInv = maxN;
    ret->nInv = 0;
    ret->vettinv = malloc(sizeof(INV) * ret->maxInv);
}

INV TABINVget(TABINV tab, char *code){
    if(tab == NULL) return NULL;
    int i;
    for(i = 0; i < tab->nInv && strcmp(tab->vettinv[i]->nome, code) != 0; i++);
    if(i < tab->nInv) return tab->vettinv[i];
    return NULL;
}

void TABINVadd(TABINV tab, INV inv){
    if(tab->nInv == tab->maxInv){
        tab->maxInv = 3*tab->maxInv/2;
        tab->vettinv = realloc(tab->vettinv, sizeof(INV)*tab->maxInv);
    }
    tab->vettinv[tab->nInv++] = inv;
}


void TABINVfree(TABINV tab){
    int i;
    for(i = 0; i < tab->nInv; i++){
        if(tab->vettinv[i] != NULL) free(tab->vettinv[i]);
    }
    free(tab->vettinv);
    free(tab);
}

void TABINVprint(TABINV tab, FILE *fp){
    int i = 0;
    INV tmp;
    for(i = 0; i < tab->nInv; i++){
        tmp = tab->vettinv[i];
        fprintf(fp, "%s %s %d %d %d %d %d %d\n", tmp->nome, tmp->tipo, tmp->stat.hp, tmp->stat.mp, tmp->stat.atk, tmp->stat.def,
               tmp->stat.mag, tmp->stat.spr);
    }
}