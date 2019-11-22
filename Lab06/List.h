//
// Created by Ruggero Nocera on 16/11/2019.
//
#include "Item.h"
#ifndef APA_LAB_LIST_H
#define APA_LAB_LIST_H
#endif //APA_LAB_LIST_H

typedef struct list *LIST;

LIST LISTinit();
void LISTsortIns(LIST l, Item val);
void LISTprint(LIST l, FILE *fp);
Item LISTsearch(LIST l, char *code);
Item LISTdeleteByCode(LIST l, char *code);
Item LISTdeleteFirstByDate(LIST l, data dataL, data dataR);