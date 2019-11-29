//
// Created by Ruggero Nocera on 29/11/2019.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct att_s{
    int i;
    int f;
    int durata;
} att;

int compatibili(att a1, att a2);
int compatibiliVett(int *sol, att *a, int pos);
void attSel(int n, att *v);
void attSelR(int pos, int *sol, int n, int currDurata, att * a, int *bestSol, int *bestDurata);

int main(){
    FILE *fp = fopen("attivita.txt", "r");
    if(fp == NULL) return -1;
    att *elenco;
    int n, i;
    fscanf(fp, "%d", &n);
    elenco = calloc(n, sizeof(struct att_s));
    printf("Attivita\' lette:\n");
    for(i = 0; i < n; i++){
        fscanf(fp, "%d,%d", &elenco[i].i, &elenco[i].f);
        elenco[i].durata = elenco[i].f - elenco[i].i;
        printf("%d, %d\n", elenco[i].i, elenco[i].f);
    }

    attSel(n, elenco);
    return 0;
}

void attSel(int n, att *v){
    int i;
    int *sol = calloc(n, sizeof(int));
    int *bestSol = calloc(n, sizeof(int));
    int bestDurata = 0;
    attSelR(0, sol, n, 0, v, bestSol, &bestDurata);
    printf("Soluzione ottima trovata: ");
    for(i = 0; i < n; i++){
        if(bestSol[i] == 1){
            printf("(%d, %d) ", v[i].i, v[i].f);
        }
    }
    printf("\nDurata totale: %d\n", bestDurata);
}

void attSelR(int pos, int *sol, int n, int currDurata, att * a, int *bestSol, int *bestDurata){
    int i;
    if(pos >= n){
        if(currDurata > *bestDurata){
            *bestDurata = currDurata;
            for(i = 0; i < n; i++){
                bestSol[i] = sol[i];
            }
        }
        return;
    }
    sol[pos] = 0;
    attSelR(pos+1, sol, n, currDurata, a, bestSol, bestDurata);
    if(compatibiliVett(sol, a, pos)){
        sol[pos] = 1;
        attSelR(pos+1, sol, n, currDurata+a[pos].durata, a, bestSol, bestDurata);
    }
}
int compatibiliVett(int *sol, att *a, int pos){
    int i;
    for(i = 0; i < pos; i++){
        if(sol[i] == 1 && !compatibili(a[i], a[pos]))
            return 0;
    }
    return 1;
}
int compatibili(att a1, att a2){ //1 -> compatibili, 0 altrimenti | tra due attività
    return !(a1.i < a2.f && a2.i < a1.f);
}