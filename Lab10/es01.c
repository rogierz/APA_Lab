//
// Created by Ruggero Nocera on 09/01/2020.
//

#include <stdio.h>
#include <stdlib.h>
#define MAX(a, b) (a >= b ? a : b)
#define filename "hard_test_set.txt"
void freeX(int gemme[4]);
void allocX(int gemme[4]);
int sol(int gemme[4]);
int fZ(int z, int r, int t, int s);
int fR(int z, int r, int t, int s);
int fT(int z, int r, int t, int s);
int fS(int z, int r, int t, int s);
int ****X;
int main() {
    int gemme[4];
    int i;
    FILE *fp = fopen(filename, "r");
    int nTest;
    fscanf(fp, "%d", &nTest);
    for (i = 0; i < nTest; i++) {
        fscanf(fp, "%d %d %d %d", &gemme[0], &gemme[1], &gemme[2], &gemme[3]);
        allocX(gemme);
        printf("TEST #%d\n", i+1);
        printf("z = %d, r = %d, t = %d, s = %d, TOT = %d\n", gemme[0], gemme[1], gemme[2], gemme[3], gemme[0]+gemme[1]+gemme[2]+gemme[3]);
        printf("Lunghezza = %d\n", sol(gemme));
        freeX(gemme);
    }
    fclose(fp);
}
void freeX(int gemme[4]){
    int j, k, l;
    for(j = 0; j <= gemme[0]; j++){
        for(k = 0; k <= gemme[1]; k++){
            for(l = 0; l <= gemme[2]; l++){
                free(X[j][k][l]);
            }
            free(X[j][k]);
        }
        free(X[j]);
    }
    free(X);
}

void allocX(int gemme[4]){
    int j, k, l, m;
    X = malloc(sizeof(int ***)*(gemme[0]+1));
    for(j = 0; j <= gemme[0]; j++){
        X[j] = malloc(sizeof(int **)*(gemme[1]+1));
        for(k = 0; k <= gemme[1]; k++){
            X[j][k] = malloc(sizeof(int *)*(gemme[2]+1));
            for(l = 0; l <= gemme[2]; l++){
                X[j][k][l] = malloc(sizeof(int)*(gemme[3]+1));
                for(m = 0; m <= gemme[3]; m++) X[j][k][l][m] = -1;
            }
        }
    }
}
int sol(int gemme[4]){
    int maxZ, maxR, maxT, maxS;
    maxZ = fZ(gemme[0], gemme[1], gemme[2], gemme[3]);
    freeX(gemme);
    allocX(gemme);
    maxR = fR(gemme[0], gemme[1], gemme[2], gemme[3]);
    freeX(gemme);
    allocX(gemme);
    maxT = fT(gemme[0], gemme[1], gemme[2], gemme[3]);
    freeX(gemme);
    allocX(gemme);
    maxS = fS(gemme[0], gemme[1], gemme[2], gemme[3]);
    return MAX(MAX(maxZ, maxR), MAX(maxT, maxS));
}

int fZ(int z, int r, int t, int s){
    if(z == 0) return 0;
    if(X[z][r][t][s] != -1) return X[z][r][t][s];
    int tmp = 1 + MAX(fZ(z-1, r, t, s), fT(z-1, r, t, s));
    if(tmp > X[z][r][t][s]) X[z][r][t][s] = tmp;
    return X[z][r][t][s];
}
int fR(int z, int r, int t, int s){
    if(r == 0) return 0;
    if(X[z][r][t][s] != -1) return X[z][r][t][s];
    X[z][r][t][s] =  1 + MAX(fZ(z, r-1, t, s), fT(z, r-1, t, s));
    return X[z][r][t][s];
}
int fT(int z, int r, int t, int s){
    if(t == 0) return 0;
    if(X[z][r][t][s] != -1) return X[z][r][t][s];
    X[z][r][t][s] = 1 + MAX(fS(z, r, t-1, s), fR(z, r, t-1, s));
    return X[z][r][t][s];
}
int fS(int z, int r, int t, int s){
    if(s == 0) return 0;
    if(X[z][r][t][s] != -1) return X[z][r][t][s];
    X[z][r][t][s] = 1 + MAX(fS(z, r, t, s-1), fR(z, r, t, s-1));
    return X[z][r][t][s];
}