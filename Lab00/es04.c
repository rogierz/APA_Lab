//
// Created by Ruggero Nocera on 04/10/2019.
//

#include <stdio.h>
#define MAX 20

int main(){
    setbuf(stdout, NULL);
    FILE *myFile;
    char fileName[MAX];
    int matrix[MAX][MAX];
    int bestMatrix[MAX][MAX];
    int nr, nc;
    int min, dim, bestDim = 0;
    int i, j, k, t;
    int somma, bestSomma;
    somma = bestSomma = 0;
    printf("Nome file: ");
    scanf("%s", fileName);
    myFile = fopen(fileName, "r");
    if(myFile == NULL) return -1;
    fscanf(myFile, "%d %d", &nr, &nc);
    min = nr;
    if(min > nc) min = nc;

    for(i = 0; i < nr; i++){
        for(j = 0; j < nc; j++){
            fscanf(myFile, "%d", &matrix[i][j]);
        }
    }
    fclose(myFile);
    while(scanf("%d", &dim) == 1 && dim > 0 && dim <= min){
        printf("\n");
            for(i = 0; i < nr-dim+1; i++) {
                for (j = 0; j < nc - dim + 1; j++) {
                    somma = 0;
                    for (k = i; k < dim + i; k++) {
                        for (t = j; t < dim + j; t++) {
                            printf("%d ", matrix[k][t]);
                            somma += matrix[k][t];
                        }
                        printf("\n");
                    }
                    if (somma > bestSomma) {
                        bestSomma = somma;
                        bestDim = dim;
                        for (k = i; k < dim + i; k++) {
                            for (t = j; t < dim + j; t++) {
                                bestMatrix[k - i][t - j] = matrix[k][t];
                            }
                        }
                    }
                    printf("-----\n");
                }
            }
    }


    printf("Matrice con la somma maggiore (%d): \n", bestSomma);
    for(i = 0; i < bestDim; i++){
        for(j = 0; j < bestDim; j++) printf("%d ", bestMatrix[i][j]);
        printf("\n");
    }
    return 0;
}
