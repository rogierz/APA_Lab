//
// Created by Ruggero Nocera on 28/11/2019.
//
#include "PG.h"
#ifndef APA_LAB_LISTPG_H
#define APA_LAB_LISTPG_H
typedef struct nodoPg_t * linkNodoPG;
typedef struct listaPg_t * LISTPG;

LISTPG LISTPGinit();
void LISTPGSortedIns(LISTPG list, PG pg);
void LISTPGdelete(LISTPG list, char* code);
PG LISTPGsearch(LISTPG list, char* code);
void LISTPGprint(LISTPG list, FILE *fp);
void LISTPGfree(LISTPG list);

#endif //APA_LAB_LISTPG_H
