//
// Created by Ruggero Nocera on 28/11/2019.
//
#include <stdio.h>

#ifndef MAXNAME
#define MAXNAME 50
#endif

#ifndef APA_LAB_INV_H
#define APA_LAB_INV_H


typedef struct inv_t* INV;
typedef struct tabInv_t* TABINV;

INV INVscan(char *inv);
struct stat_t INVgetStat(INV inv);

TABINV TABINVinit(int maxN);
void TABINVadd(TABINV tab, INV inv);
INV TABINVget(TABINV tab, char *code);
void TABINVfree(TABINV tab);
void TABINVprint(TABINV tab, FILE *fp);
#endif //APA_LAB_INV_H
