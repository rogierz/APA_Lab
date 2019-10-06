//
// Created by Ruggero Nocera on 04/10/2019.
//

#include <stdio.h>
#include <stdlib.h>
#define MAX 20

int main(){
    FILE* campionato;
    char campionatoNomeFile[20];
    int n, m;
    int i, j;
    int campionatoMatrix[MAX][MAX];
    int bestPunteggio, bestIndex;
    printf("Nome file: ");
    scanf("%s", campionatoNomeFile);
    campionato = fopen(campionatoNomeFile, "r");
    if(campionato == NULL)  return -1;
    fscanf(campionato, "%d %d", &n, &m);
    int *punteggioSquadre = calloc(sizeof(int), n);
    if(punteggioSquadre == NULL) return -1;

    for(i = 0; i < n; i++){
        for(j = 0; j < m; j++){
            fscanf(campionato, "%d", &campionatoMatrix[i][j]);
        }
    }

    for(j = 0; j < m; j++){
        bestPunteggio = bestIndex = 0;
        for(i = 0; i < n; i++) punteggioSquadre[i] += campionatoMatrix[i][j];
        for(i = 0; i < n; i++){
            if (punteggioSquadre[i] > bestPunteggio){
                bestIndex = i;
                bestPunteggio = punteggioSquadre[i];
            }
        }
        printf("Nella giornata #%d la capolista e\' la squadra #%d\n", j+1, bestIndex+1);
    }

    free(punteggioSquadre);
    fclose(campionato);
    return 0;
}