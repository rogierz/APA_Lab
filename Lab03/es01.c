//
// Created by Ruggero Nocera on 25/10/2019.
//

#include <stdio.h>
#define fileName "file.txt"
#define MAX 50

typedef struct subMatrice{
    int nr, nc;
    int i, j;
    int area;
} subMatrice;

int leggiMatrice (int matr[][MAX], int max, int *nr, int *nc);
int riconosciRegione(int matr[][MAX], int nr, int nc, int r, int c, int *b, int *h);

int main(){

    int nr, nc;
    int i, j;
    int matrice[MAX][MAX];
    subMatrice bestArea, bestAltezza, bestLarghezza, tmp;

    bestArea.area = -1;
    bestAltezza.nr = -1;
    bestLarghezza.nc = -1;

    if(leggiMatrice(matrice, MAX, &nr, &nc) == -1) return -1;

    for(i = 0; i < nr; i++) {
        for (j = 0; j < nc; j++) {
            if(riconosciRegione(matrice, nr, nc, i, j, &tmp.nc, &tmp.nr)){
                tmp.i = i;
                tmp.j = j;
                tmp.area = tmp.nr * tmp.nc;
                if (tmp.nr > bestAltezza.nr) bestAltezza = tmp;
                if (tmp.nc > bestLarghezza.nc) bestLarghezza = tmp;
                if (tmp.area > bestArea.area) bestArea = tmp;
            }
        }
    }

    printf("Max Base: estr.sup. SX <%d, %d> b=%d, h=%d, Area=%d\n", bestLarghezza.i, bestLarghezza.j, bestLarghezza.nc, bestLarghezza.nr, bestLarghezza.area);
    printf("Max Area: estr.sup. SX <%d, %d> b=%d, h=%d, Area=%d\n", bestArea.i, bestArea.j, bestArea.nc, bestArea.nr, bestArea.area);
    printf("Max Altezza: estr.sup. SX <%d, %d> b=%d, h=%d, Area=%d\n", bestAltezza.i, bestAltezza.j, bestAltezza.nc, bestAltezza.nr, bestAltezza.area);
    return 0;
}

int leggiMatrice (int matr[][MAX], int max, int *nr, int *nc){
    FILE *fileMatrice = fopen(fileName, "r");
    int i, j;
    if(fileMatrice == NULL) return -1;
    fscanf(fileMatrice, "%d %d", nr, nc);
    for(i = 0; i < *nr; i++){
        for(j = 0; j < *nc; j++){
            fscanf(fileMatrice, "%d", &matr[i][j]);
        }
    }
    fclose(fileMatrice);
    return 0;
}

int riconosciRegione(int matr[][MAX], int nr, int nc, int r, int c, int *b, int *h) {
    int inizio;
    inizio = 1;
    if (matr[r][c] == 1) {
        if (r > 0 && c > 0) {
            if (matr[r - 1][c] == 1 || matr[r][c - 1] == 1) {
                inizio = 0;
            }
        } else {
            if (c > 0) {
                if (matr[r][c - 1] == 1) inizio = 0;
            } else if (r > 0) {
                if (matr[r - 1][c] == 1) inizio = 0;
            }
        }
        if(inizio){
            for (*h = 0; matr[r + *h][c] != 0 && r + *h < nr; (*h)++);
            for (*b = 0; matr[r][c + *b] != 0 && c + *b < nc; (*b)++);
        }
        return inizio;
    }
}