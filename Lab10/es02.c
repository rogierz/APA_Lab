//
// Created by Ruggero Nocera on 09/01/2020.
//
#include <stdio.h>
#include <stdlib.h>
#define MAXNAME 100
#define fileName "elementi.txt"
#define DD 10
#define DP 35
#define NDIAG 3
#define NELEM 5

typedef struct elem_s{
    char nome[MAXNAME];
    int tipo;
    int ingresso;
    int uscita;
    int prec;
    int finale;
    float val;
    int diff;
} elem_t;

void bestSol(elem_t *elementi, int n);
void bestSolR(int pos, int diag, int **sol, int **bestSolM, float *tot, elem_t *elementi, int n, int dd, int dp);
int checkSol(int **sol, elem_t *elementi);
float computeValue(int **sol, elem_t *elementi);
void readElem(FILE *fp, elem_t *e){
    fscanf(fp, "%s %d %d %d %d %d %f %d", e->nome, &(e->tipo), &(e->ingresso), &(e->uscita), &(e->prec), &(e->finale), &(e->val), &(e->diff));
}
int main(){
    setbuf(stdout, NULL);
    elem_t *elementi;
    int nElementi, i;
    FILE *fp = fopen(fileName, "r");
    if(fp == NULL) return -1;
    fscanf(fp, "%d", &nElementi);
    elementi = malloc(sizeof(elem_t)*nElementi);
    for(i = 0; i < nElementi; i++){
        readElem(fp, &elementi[i]);
    }
    bestSol(elementi, nElementi);
}

void bestSol(elem_t *elementi, int n){
    int **sol = malloc(sizeof(int *)*NDIAG);
    int **bestSolM = malloc(sizeof(int *)*NDIAG);
    float tot = 0;
    int i, j;
    for(i = 0; i < NDIAG; i++){
        sol[i] = malloc(sizeof(int)*NELEM);
        bestSolM[i] = malloc(sizeof(int)*NELEM);
        for(j = 0; j < NELEM; j++){
            sol[i][j] = -1;
        }
    }
    bestSolR(0, 0, sol, bestSolM, &tot, elementi, n, 0, 0);
    printf("DD = %d DP = %d\n", DD, DP);
    printf("TOT = %.3f\n", tot);
    for(i = 0; i < NDIAG; i++){
        printf("DIAG #%d\n", i+1);
        for(j = 0; j < NELEM && elementi[bestSolM[i][j]].finale == 0 && bestSolM[i][j] != -1; j++){
            printf("%s ", elementi[bestSolM[i][j]].nome);
        }
        printf("\n");
    }
}

void bestSolR(int pos, int diag, int **sol, int **bestSolM, float *tot, elem_t *elementi, int n, int dd, int dp){
    int i, j;
    float value;
    if(diag >= NDIAG){
      if(checkSol(sol, elementi)){
            value = computeValue(sol, elementi);
            if(value > *tot){

                *tot = value;
                for(i = 0; i < NDIAG; i++){
                    for(j = 0; j < NELEM ; j++){
                        bestSolM[i][j] = sol[i][j];
                    }
                }
            }
        }
        return;
    }
    for(i = 0; i < n; i++){
        if(pos == 0){
            if(elementi[i].ingresso == 0) continue;
            if(elementi[i].prec == 1) continue;
        }
        if(pos > 0){
            if(elementi[i].ingresso != elementi[sol[diag][pos-1]].uscita) continue;
        }
        if(dd + elementi[i].diff > DD || dp + elementi[i].diff > DP) continue;
        sol[diag][pos] = i;
        bestSolR(pos+1, diag, sol, bestSolM, tot, elementi, n, dd + elementi[i].diff, dp + elementi[i].diff);
    }
    if(pos > 0){
        sol[diag][pos] = -1;
        bestSolR(0, diag+1, sol, bestSolM, tot, elementi, n, 0, dp);
    }
    return;
}

int checkSol(int **sol, elem_t *elementi){ // 0 non valida, 1 valida
    int i, j;
    int acrob = 0;
    int avanti = 0;
    int indietro = 0;
    int seq = 0;
    for(i = 0; i < NDIAG; i++){
        acrob = 0;
        for(j = 0; j < NELEM && sol[i][j] != -1; j++){
            if(elementi[sol[i][j]].tipo != 0){
                acrob = 1;
                if(j > 0 && elementi[sol[i][j-1]].tipo != 0) seq = 1;
            }
            if(elementi[sol[i][j]].tipo == 2) avanti = 1;
            if(elementi[sol[i][j]].tipo == 1) indietro = 1;
        }
        if(!acrob) return 0;
    }
    if(!avanti || !indietro) return 0;
    if(!seq) return 0;
    return 1;
}

float computeValue(int **sol, elem_t *elementi){
    int i, j;
    float diag[NDIAG];
    diag[0] = diag[1] = diag[2] = 0.0;
    float coeff = 1.0;
    for(i = 0; i < NDIAG; i++){
        for(j = 0; j < NELEM && sol[i][j] != -1; j++){
            diag[i] += elementi[sol[i][j]].val;
            if(i == 2){
                if(elementi[sol[i][j]].diff >= 8.0) coeff = 1.5;
            }
        }
    }
    diag[2] = diag[2]*coeff;
    return diag[0]+diag[1]+diag[2];
}