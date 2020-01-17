//
// Created by Ruggero Nocera on 17/01/2020.
//

#include "ST.h"
#include <stdlib.h>
#include <string.h>
struct symboltable{
    char **a;
    int N;
    int M;
};

ST STinit(int maxN){
    ST ret = malloc(sizeof(*ret));
    ret->a = malloc(sizeof(char *)*maxN);
    for(int i = 0; i < maxN; i++) ret->a[i] = NULL;
    ret->N = 0;
    ret->M = maxN;
    return ret;
}

void STinsert(ST st, char *code){
    if(st->N == st->M){
        st->a = realloc(st->a, st->M*2*sizeof(char *));
        st->M = st->M*2;
    }
    st->a[st->N++] = strdup(code);
}

int STsearch(ST st, char *code){
    int i;
    for(i = 0; i < st->N && strcmp(code, st->a[i]) != 0; i++);
    if(i == st->N) return -1;
    return i;
}

char *STsearchByIndex(ST st, int index){
    return strdup(st->a[index]);
}

int STcount(ST st){
    return st->N;
}

void STfree(ST st){
    int i = 0;
    for (i = 0; i < st->N; i++)
        free(st->a[i]);
    free(st->a);
    free(st);
}