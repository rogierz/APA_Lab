//
// Created by Ruggero Nocera on 17/10/2019.
//

#include <stdio.h>
#define fileName "file.txt"
#define MAX 50

typedef struct subMatrice{
    int nr, nc;
    int i, j;
    int area;
} subMatrice;

int main(){
    FILE *fileMatrice = fopen(fileName, "r");
    if(fileMatrice == NULL) return -1;
    int nr, nc;
    int i, j;
    int matrice[MAX][MAX];
    int inizio = 0;
    subMatrice bestArea, bestAltezza, bestLarghezza, tmp;

    bestArea.area = -1;
    bestAltezza.nr = -1;
    bestLarghezza.nc = -1;

    fscanf(fileMatrice, "%d %d", &nr, &nc);
    for(i = 0; i < nr; i++){
        for(j = 0; j < nc; j++){
            fscanf(fileMatrice, "%d", &matrice[i][j]);
        }
    }

    for(i = 0; i < nr; i++) {
        for (j = 0; j < nc; j++) {
            inizio = 1;
            if (matrice[i][j] == 1) {
                if (i > 0 && i < nr && j > 0 && j < nc) {
                    if (matrice[i - 1][j] == 1 || matrice[i][j - 1] == 1) {
                        inizio = 0;
                    }
                } else {
                    if (j > 0) {
                        if (matrice[i][j - 1] == 1) inizio = 0;
                    } else if (i > 0) {
                        if (matrice[i - 1][j] == 1) inizio = 0;
                    }
                }
                if(inizio){
                    tmp.i = i;
                    tmp.j = j;
                    tmp.nr = tmp.nc = 0;
                    for(tmp.nr = 0; matrice[i+tmp.nr][j] != 0 && i+tmp.nr < nr; tmp.nr++);
                    for(tmp.nc = 0; matrice[i][j+tmp.nc] != 0 && j+tmp.nc < nc; tmp.nc++);
                    tmp.area = tmp.nr*tmp.nc;
                    if(tmp.nr > bestAltezza.nr) bestAltezza = tmp;
                    if(tmp.nc > bestLarghezza.nc) bestLarghezza = tmp;
                    if(tmp.area > bestArea.area) bestArea = tmp;
                }
            }
        }
    }

    printf("Max Base: estr.sup. SX <%d, %d> b=%d, h=%d, Area=%d\n", bestLarghezza.i, bestLarghezza.j, bestLarghezza.nc, bestLarghezza.nr, bestLarghezza.area);
    printf("Max Area: estr.sup. SX <%d, %d> b=%d, h=%d, Area=%d\n", bestArea.i, bestArea.j, bestArea.nc, bestArea.nr, bestArea.area);
    printf("Max Altezza: estr.sup. SX <%d, %d> b=%d, h=%d, Area=%d\n", bestAltezza.i, bestAltezza.j, bestAltezza.nc, bestAltezza.nr, bestAltezza.area);
    fclose(fileMatrice);
    return 0;
}