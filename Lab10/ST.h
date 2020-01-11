//
// Created by Ruggero Nocera on 10/01/2020.
//

#ifndef APA_LAB_ST_H
#define APA_LAB_ST_H

#include "ITEM.h"
typedef struct symboltable *ST;
ST STinit(int maxN);
int STcount(ST st);
void STfree(ST st);
void STinsert(ST st, ITEM i, int index);
int STsearch(ST st, char *label);
char *STsearchByIndex(ST st, int index);
#endif //APA_LAB_ST_H
