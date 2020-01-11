//
// Created by Ruggero Nocera on 10/01/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "GRAPH.h"
#include "ST.h"
#include "ITEM.h"
#define fileName "grafo.txt"
#define MAXL 30
GRAPH fileRead(FILE *fp, ST *tmp, ITEM **vertex, int *n, int *m);

int main(){
    setbuf(stdout, NULL);
    FILE *fp = fopen(fileName, "r");
    if(fp == NULL) return -1;
    ITEM *vertex;
    int nVertex;
    int maxVertex;
    ST itemST;
    GRAPH G = fileRead(fp, &itemST, &vertex, &nVertex, &maxVertex);
    GRAPHsetTab(G, itemST);
    GRAPHprintVertex(G);
    /*char **subg = malloc(sizeof(char *)*3);
    printf("Inserisci il nome dei tre vertici: ");
    for(int i = 0; i < 3; i++){
        subg[i] = malloc(sizeof(char)*MAXL);
        scanf("%s", subg[i]);
    }
    GRAPHthreeCompleteSubGMATRIX(G, subg);*/
    GRAPHgenerateLadj(G);
    GRAPHprintLadj(G);
    return 0;
}

GRAPH fileRead(FILE *fp, ST *tmp, ITEM **vertex, int *n, int *m){
    GRAPH G;
    ITEM it1, it2;
    int id1, id2;
    int wt;
    char label1[30], label2[30];
    *tmp = STinit(4);
    int M = 4;
    *vertex = malloc(sizeof(**vertex)*M);
    *n = 0;
    while(!feof(fp)){
        fscanf(fp, "%s %s", label1, label2);
        it1 = ITEMnew(label1, label2);
        id1 = STsearch(*tmp, label1);
        fscanf(fp, "%s %s %*d", label1, label2);
        it2 = ITEMnew(label1, label2);
        id2 = STsearch(*tmp, label1);
        if(id1 < 0){
            STinsert(*tmp, it1, STcount(*tmp));
            if(*n == M){
                M = M*2;
                *vertex = realloc(*vertex, sizeof(**vertex)*M);
            }
            (*vertex)[(*n)++] = it1;
        }else{
            free(it1);
            it1 = NULL;
        }
        if(id2 < 0){
            STinsert(*tmp, it2, STcount(*tmp));
            if(*n == M){
                M = M*2;
                *vertex = realloc(*vertex, sizeof(**vertex)*M);
            }
            (*vertex)[(*n)++] = it2;
        }else{
            free(it2);
            it2 = NULL;
        }
    }
    G = GRAPHinit(STcount(*tmp));
    rewind(fp);
    while(fscanf(fp, "%s %*s %s %*s %d", label1, label2, &wt) == 3){
        id1 = STsearch(*tmp, label1);
        id2 = STsearch(*tmp, label2);
        if(id1 >= 0 && id2 >= 0)
            GRAPHinsertE(G, id1, id2, wt);
    }
    *m = M;
    return G;
}

