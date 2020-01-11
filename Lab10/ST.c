//
// Created by Ruggero Nocera on 10/01/2020.
//

#include "ST.h"
#include <string.h>
#include "ITEM.h"
#include <stdlib.h>
#define MAXC 20

struct symboltable{
    char **a;
    int N;
    int M;
};

ST STinit(int maxN){
    int i;
    ST st;
    st = malloc(sizeof(*st));
    st->a = malloc(sizeof(char *)*maxN);
    for(i = 0; i < maxN; i++){
        st->a[i] = malloc(sizeof(char)*MAXC);
        st->a[i][0] = '\0';
    }
    st->N = 0;
    st->M = maxN;
    return st;
}

int STcount(ST st){
    return st->N;
}

void STfree(ST st){
    int i;
    for(i = 0; i < st->M; i++){
        free(st->a[i]);
    }
    free(st->a);
    free(st);
}

void STinsert(ST st, ITEM i, int index){
    int j;
    if(st->N == st->M){
        st->a = realloc(st->a, sizeof(char *)*st->M*2);
        st->M = st->M*2;
        for(j = st->N; j < st->M; j++)
            st->a[j] = malloc(sizeof(char)*MAXC);
    }
    strncpy(st->a[index], ITEMgetLabel(i), MAXC);
    st->N++;
}

int STsearch(ST st, char *label){
    int i;
    for(i = 0; i < st->N; i++){
        if(strcmp(label, st->a[i]) == 0) return i;
    }
    return -1;
}

char *STsearchByIndex(ST st, int index){
    return strdup(st->a[index]);
}