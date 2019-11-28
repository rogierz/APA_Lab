//
// Created by Ruggero Nocera on 28/11/2019.
//
#include <stdio.h>
#include "INV.h"


#ifndef APA_LAB_PG_H
#define APA_LAB_PG_H

struct stat_t{
    unsigned int hp;
    unsigned int mp;
    unsigned int atk;
    unsigned int def;
    unsigned int mag;
    unsigned int spr;
};
typedef struct pg_t *PG;
void PGfree(PG pg);
int PGcmp(PG pg1, PG pg2);
int PGcmpCode(PG pg, char *code);
PG PGnull();
void PGprint(PG pg, FILE* fp);
struct stat_t PGgetStat(PG pg, FILE* fp);
PG PGscan(char * pg);
void PGaddINV(PG pg, INV inv);
void PGremoveINV(PG pg, INV inv);

#endif //APA_LAB_PG_H
