//
// Created by Ruggero Nocera on 28/11/2019.
//

#include "PG.h"
#include "INV.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef MAXNAME
#define MAXNAME 50
#endif



struct equip_t{
    int inUso;
    int maxDim;
    INV *vettEq;
};
struct pg_t{
    char codice[MAXNAME];
    char nome[MAXNAME];
    char classe[MAXNAME];
    struct equip_t equip;
    struct stat_t stat;
    struct stat_t tot;
};

PG PGnull(){
    return NULL;
}
int PGcmp(PG pg1, PG pg2){
    if(pg1 == pg2) return 0;
    if(pg1 != NULL && pg2 != NULL){
        return strcmp(pg1->codice, pg2->codice);
    }
    if(pg1 == NULL) return -1;
    //if(pg2 == NULL)
    return 1;
}

int PGcmpCode(PG pg, char *code){
    return strcmp(pg->codice, code);
}
void PGfree(PG pg){
    if(pg->equip.vettEq != NULL) free(pg->equip.vettEq);
    free(pg);
}

PG PGscan(char * pg){
    PG ret = malloc(sizeof(struct pg_t));
    ret->equip.vettEq = NULL;
    if(PGcmp(ret, PGnull()) == 0) return PGnull();
    if(sscanf(pg, "%s %s %s %d %d %d %d %d %d", ret->codice, ret->nome, ret->classe, &(ret->stat.hp), &(ret->stat.mp), &(ret->stat.atk), &(ret->stat.def),
           &(ret->stat.mag), &(ret->stat.spr)) != 9){
        PGfree(ret);
        return PGnull();
    }
    ret->tot = ret->stat;
    ret->equip.inUso = 0;
    ret->equip.maxDim = 10;
    ret->equip.vettEq = malloc(ret->equip.maxDim*sizeof(INV));
    if(ret->equip.vettEq == NULL){
        PGfree(ret);
        return PGnull();
    }
    return ret;
}

void PGprint(PG pg, FILE *fp){
    fprintf(fp, "%s %s %s %d %d %d %d %d %d\n", pg->codice, pg->nome, pg->classe, pg->tot.hp, pg->tot.mp, pg->tot.atk, pg->tot.def,
           pg->tot.mag, pg->tot.spr);
}

void PGaddINV(PG pg, INV inv){
    if(pg->equip.inUso == pg->equip.maxDim){
        pg->equip.maxDim = 3*pg->equip.maxDim/2;
        pg->equip.vettEq = realloc(pg->equip.vettEq, pg->equip.maxDim* sizeof(INV));
    }
    pg->equip.vettEq[pg->equip.inUso++] = inv;
    PGgetStat(pg, NULL);
}

void PGremoveINV(PG pg, INV inv){
    int i = 0, j;
    for(i = 0; i < pg->equip.inUso && inv != pg->equip.vettEq[i]; i++);
    if(i != pg->equip.inUso){
        for(j = i; j < pg->equip.inUso-1; j++){
            pg->equip.vettEq[j] = pg->equip.vettEq[j+1];
        }
        pg->equip.inUso--;
    }
    PGgetStat(pg, NULL);
}

struct stat_t PGgetStat(PG pg, FILE* fp){
    int i;
    struct stat_t ret;
    struct stat_t tmp;
    ret.hp = 0;
    ret.mp = 0;
    ret.atk = 0;
    ret.def = 0;
    ret.mag = 0;
    ret.spr = 0;
    pg->tot = ret;
    for(i = 0; i < pg->equip.inUso; i++){
        tmp = INVgetStat(pg->equip.vettEq[i]);
        ret.hp += tmp.hp;
        ret.mp += tmp.mp;
        ret.atk += tmp.atk;
        ret.def += tmp.def;
        ret.mag += tmp.mag;
        ret.spr += tmp.spr;
    }
    if(ret.hp + pg->stat.hp >= 1) pg->tot.hp = ret.hp + pg->stat.hp;
    if(ret.mp + pg->stat.mp >= 1) pg->tot.mp = ret.mp + pg->stat.mp;
    if(ret.atk +  pg->stat.atk >= 1) pg->tot.atk = ret.atk +  pg->stat.atk;
    if(ret.def + pg->stat.def >= 1) pg->tot.def = ret.def + pg->stat.def;
    if(ret.mag + pg->stat.mag >= 1) pg->tot.mag = ret.mag + pg->stat.mag;
    if(ret.spr + pg->stat.spr >= 1) pg->tot.spr = ret.spr + pg->stat.spr;
    if(fp != NULL) PGprint(pg, fp);
    return pg->tot;
}