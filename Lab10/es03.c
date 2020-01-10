//
// Created by Ruggero Nocera on 10/01/2020.
//

#include <stdio.h>
#include <stdlib.h>
#define MAXNAME 100
#define NDIAG 3
#define NELEM 5
#define DD 10
#define DP 20
#define fileName "elementi.txt"

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

void readElem(FILE *fp, elem_t *e);
void mergeSortR(elem_t *e, elem_t *tmp, int l, int r);
void ordinaElementi(elem_t *e, int n);
void buildSol(int **sol, elem_t *e, int n);
int greedyDiag1(int **sol, elem_t *e, int n, int dp);
int greedyDiag2(int **sol, elem_t *e, int n, int dp);
int greedyDiag3(int **sol, elem_t *e, int n, int dp);
int main(){
    elem_t *elementi;
    int i, j, nElementi;
    int **sol;
    sol = malloc(NDIAG* sizeof(int *));
    for(i = 0; i < NDIAG; i++){
        sol[i] = malloc(NELEM* sizeof(int));
    }
    FILE *fp = fopen(fileName, "r");
    fscanf(fp, "%d", &nElementi);
    elementi = malloc(sizeof(elem_t)*nElementi);
    for(i = 0; i < nElementi; i++){
        readElem(fp, &elementi[i]);
    }
    ordinaElementi(elementi, nElementi);
    buildSol(sol, elementi, nElementi);
    for(i = 0; i < NDIAG; i++){
        printf("DIAG #%d\n", i+1);
        for(j = 0; j < NELEM; j++){
            if(sol[i][j] != -1){
                printf("%s ", elementi[sol[i][j]].nome);
            }
        }
        printf("\n");
    }
    return 0;
}

void buildSol(int **sol, elem_t *e, int n){
    //TODO
}
int greedyDiag1(int **sol, elem_t *e, int n, int dp){
    //TODO
}
int greedyDiag2(int **sol, elem_t *e, int n, int dp){
    //TODO
}
int greedyDiag3(int **sol, elem_t *e, int n, int dp){
    //TODO
}

void readElem(FILE *fp, elem_t *e){
    fscanf(fp, "%s %d %d %d %d %d %f %d", e->nome, &(e->tipo), &(e->ingresso), &(e->uscita), &(e->prec), &(e->finale), &(e->val), &(e->diff));
}

void ordinaElementi(elem_t *e, int n){
    elem_t *tmp = malloc(sizeof(elem_t)*n);
    mergeSortR(e, tmp, 0, n-1);
    free(tmp);
}

void merge(elem_t *e, elem_t *tmp, int l, int m, int r){
    int i, j, k;
    i = l;
    j = m+1;
    for(k = l; k <= r; k++){
        if(i > m)
            tmp[k] = e[j++];
        else if(j > r)
            tmp[k] = e[i++];
        else if(e[i].tipo != 0 && e[j].tipo == 0)
            tmp[k] = e[i++];
        else if(e[i].val >= e[j].val)
            tmp[k] = e[i++];
        else
            tmp[k] = e[j++];
    }
    for(k = l; k <= r; k++){
        e[k] = tmp[k];
    }
}
void mergeSortR(elem_t *e, elem_t *tmp, int l, int r){
    if(l>=r) return;
    int m = (l+r)/2;
    mergeSortR(e, tmp, l, m);
    mergeSortR(e, tmp, m+1, r);
    merge(e, tmp, l, m, r);
}
