//
// Created by Ruggero Nocera on 17/01/2020.
//

#ifndef APA_LAB_ST_H
#define APA_LAB_ST_H

typedef struct symboltable *ST;
ST STinit(int maxN);
void STinsert(ST st, char *code);
int STsearch(ST st, char *code);
char *STsearchByIndex(ST st, int index);
int STcount(ST st);
void STfree(ST st);
#endif //APA_LAB_ST_H
