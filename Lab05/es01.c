//
// Created by Ruggero Nocera on 09/11/2019.
//

#include <stdio.h>
#include <stdlib.h>

#define braniFileName "brani.txt"
#define MAX 255

typedef struct{
    char **canzoni;
    int numCanzoni;
} Item;
int stampa(int pos, Item* livelli, int n, char** sol, int count);
int main(){
    Item *amici;
    char **playlist;
    int numAmici;
    int i, j;
    FILE *fp = fopen(braniFileName, "r");
    if(fp == NULL) return -1;
    fscanf(fp, "%d", &numAmici);
    amici = calloc(numAmici, sizeof(Item));
    playlist = calloc(numAmici, sizeof(char *));
    for(i = 0; i < numAmici; i++){
        fscanf(fp, "%d", &amici[i].numCanzoni);
        amici[i].canzoni = calloc(amici[i].numCanzoni, sizeof(char *));
        //playlist[i] = calloc(MAX, sizeof(char));
        for(j = 0; j < amici[i].numCanzoni; j++){
            amici[i].canzoni[j] = calloc(MAX, sizeof(char));
            fscanf(fp, "%s", amici[i].canzoni[j]);
        }
    }
    printf("\n\nHo generato un totale di %d playlist.", stampa(0, amici, numAmici, playlist, 0));

    for(i = 0; i < numAmici; i++){
        for(j = 0; j < amici[i].numCanzoni; j++){
            free(amici[i].canzoni[j]);
        }
        free(amici[i].canzoni);
    }
    free(amici);
}

int stampa(int pos, Item* livelli, int n, char** sol, int count){
    int i;
    if(pos >= n){
        printf("Playlist possibile: \n");
        for(i = 0; i < n; i++){
            printf("\tAmico %d:\t%s\n", i+1, sol[i]);
        }
        return count + 1 ;
    }

    for(i = 0; i < livelli[pos].numCanzoni; i++){
        sol[pos] = livelli[pos].canzoni[i];
        count = stampa(pos+1, livelli, n, sol, count);
    }
    return count;
}