//
// Created by Ruggero Nocera on 12/12/2019.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) a >= b ? a : b
typedef struct att_s{
    int i;
    int f;
    int durata;
} att;

int compatibili(att a1, att a2);
int solR(att *elenco, int i);
int sol(att* elenco, int n);
int solDP(att *elenco, int n, int *L, int *P);
void solPrint(att *elenco, int *P, int last);
int main(){
    FILE *fp = fopen("attivita.txt", "r");
    if(fp == NULL) return -1;
    att *elenco;
    int n, i, *L, *P;
    fscanf(fp, "%d", &n);
    elenco = calloc(n, sizeof(struct att_s));
    L = calloc(n, sizeof(int));
    P = calloc(n, sizeof(int));
    printf("Attivita\' lette:\n");
    for(i = 0; i < n; i++){
        fscanf(fp, "%d,%d", &elenco[i].i, &elenco[i].f);
        elenco[i].durata = elenco[i].f - elenco[i].i;
        printf("%d, %d\n", elenco[i].i, elenco[i].f);
    }

    printf("Sol ottima ricorsiva: %d\n", sol(elenco, n));
    int last = solDP(elenco, n, L, P);
    printf("Sol ottima programmazione dinamica: %d\n", L[last]);
    solPrint(elenco, P, last);
    return 0;
}
void solPrint(att *elenco, int *P, int last){
    if(P[last] == -1){
        printf("(%d, %d) ", elenco[last].i, elenco[last].f);
        return;
    }
    solPrint(elenco, P, P[last]);
    printf("(%d, %d) ", elenco[last].i, elenco[last].f);
}
int solDP(att *elenco, int n, int *L, int *P){
    int i, j, ris = elenco[0].durata, last = 0;
    P[0] = -1;
    L[0] = elenco[0].durata;
    for(i = 1; i < n; i++){
        P[i] = -1;
        L[i] = elenco[i].durata;
        for(j = 0; j < i; j++){
            if(compatibili(elenco[i], elenco[j]) && L[i] <= elenco[i].durata + L[j]){
                P[i] = j;
                L[i] = elenco[i].durata + L[j];
            }
        }
        if(L[i] >= ris){
            ris = L[i];
            last = i;
        }
    }
    return last;
}
int compatibili(att a1, att a2){ //1 -> compatibili, 0 altrimenti | tra due attività
    return !(a1.i < a2.f && a2.i < a1.f);
}

int sol(att* elenco, int n){
    int i, max = 0, tmp;
    for(i = 0; i < n; i++){
        tmp = solR(elenco, i);
        if(tmp > max) max = tmp;
    }
    return max;
}
int solR(att *elenco, int i){
    int j, ret;
    ret = elenco[i].durata;
    for(j = 0; j < i; j++){
        if(compatibili(elenco[j], elenco[i]))
            ret = MAX(ret, elenco[i].durata + solR(elenco, j));
    }
    return ret;
}