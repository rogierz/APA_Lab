//
// Created by Ruggero Nocera on 16/11/2019.
//
#include <stdio.h>
#ifndef APA_LAB_ITEM_H
#define APA_LAB_ITEM_H
#define MAX 50


typedef struct{
    int gg;
    int mm;
    int aaaa;
    int dataToInt;
} data;

typedef struct{
    char codice[6];
    char nome[MAX];
    char cognome[MAX];
    data nascita;
    char via[MAX];
    char citta[MAX];
    int cap;
} Item;

Item ITEMnull();
Item ITEMscan(char *s);
void ITEMprint(Item tmp, FILE* fp);
int ITEMcmp (Item a1, Item a2);
int ITEMcmpCode(Item a1, char *code);
char *ITEMgetCode(Item a);

#endif //APA_LAB_ITEM_H