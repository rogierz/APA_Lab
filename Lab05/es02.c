//
// Created by Ruggero Nocera on 10/11/2019.
//

#include <stdio.h>
#include <stdlib.h>
#define fileName "matr.txt"

int **malloc2dR(int nr, int nc);
void malloc2dP(int ***p, int nr, int nc);
void free2d(int **p, int nr);
void separa(int **matr, int nr, int nc, int *b, int *w);
int main(){
    FILE *fp = fopen(fileName, "r");
    if(fp == NULL) return -1;
    int **matr;
    int nr, nc;
    int i, j;
    int *white, *black;
    fscanf(fp, "%d %d", &nr, &nc);
    matr = malloc2dR(nr, nc);
    //malloc2dP(&matr, nr, nc);
    black = calloc(nr*nc/2+1, sizeof(int));
    white = calloc(nr*nc/2, sizeof(int));

    for(i = 0; i < nr; i++){
        for(j = 0; j < nc; j++){
            fscanf(fp, "%d", &matr[i][j]);
        }
    }
    separa(matr, nr, nc, black, white);
    printf("Caselle nere: ");
    for(i = 0; i < nr*nc/2+1; i++) printf("%d ", black[i]);
    printf("\nCaselle bianche: ");
    for(i = 0; i < nr*nc/2; i++) printf("%d ", white[i]);
    free(black);
    free(white);
    free2d(matr, nr);
    return 0;
}
void separa(int **matr, int nr, int nc, int *b, int *w){
    int i, j;
    int k = 0;
    for(i = 0; i < nr; i++){
        for(j = 0; j < nc; j++){
            if((i*nr+j) % 2 == 0){
                b[k] = matr[i][j];
            }else{
                w[k++] = matr[i][j];
            }
        }
    }
}
int **malloc2dR(int nr, int nc){
    int **matr = calloc(nr, sizeof(int *));
    int i;
    for(i = 0; i < nr; i++) matr[i] = calloc(nc, sizeof(int));
    return matr;
}

void malloc2dP(int ***p, int nr, int nc){
    int i;
    *p = calloc(nr, sizeof(int *));
    for(i = 0; i < nr; i++) *p[i] = calloc(nc, sizeof(int));
}

void free2d(int **p, int nr){
    int i;
    for(i = 0; i < nr; i++) free(p[i]);
    free(p);
}