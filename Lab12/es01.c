//
// Created by Ruggero Nocera on 17/01/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "GRAPH.h"
#include <limits.h>
void generaGraphToDag(GRAPH G);

int main(int argc, char *argv[]){
    setbuf(stdout, NULL);
    if(argc < 2)
        return -1;
    int N = argc-1;
    GRAPH *G = malloc(sizeof(*G)*N);
    int *cyc = calloc(N, sizeof(int));
    FILE *fp;
    for(int i = 0; i < N; i++){
        fp = fopen(argv[i+1], "r");
        G[i] = GRAPHload(fp);
        if(GRAPHdfsSearchCycle(G[i])){
            printf("Ho trovato un ciclo nel grafo #%d\n", i+1);
            cyc[i] = 1;
        }
        fclose(fp);
    }
    for(int i = 0; i < N; i++){
        if(cyc[i] == 1){
            printf("Genero il set di archi da rimuovere per rendere il grafo #%d un DAG:\n", i+1);
            generaGraphToDag(G[i]);
            printf("Il DAG ottenuto e\'\n");
            GRAPHstore(G[i], stdout);
            printf("I Max Path sono:\n");
            for(int j = 0; j < GRAPHgetV(G[i]); j++){
                DAGmaxPath(G[i], j);
            }
        }
        GRAPHfree(G[i]);
    }
}
void generaR(int pos, int start, EDGE *edges, int E, int *sol, int card, int *bestSol, int *bestWt, GRAPH G, int *search){
    int i;
    int wt = 0;
    if(pos >= card){
        printf("Provo con gli archi:\n");
        for(i = 0; i < card; i++){
            EDGEstore(G, edges[sol[i]], stdout);
            GRAPHremoveE(G, edges[sol[i]]);
        } printf("\n");
        if(!GRAPHdfsSearchCycle(G)){
            *search = 0;
            for (i = 0; i < card; i++)
                wt += edges[sol[i]].wt;
            if (wt > *bestWt) {
                *bestWt = wt;
                for (i = 0; i < card; i++)
                    bestSol[i] = sol[i];
            }
        }

        for(i = 0; i < card; i++)
                GRAPHinsertE(G, edges[sol[i]].v, edges[sol[i]].w, edges[sol[i]].wt);
        return;
    }
    for(i = start; i < E; i++){
        sol[pos] = i;
        generaR(pos+1, i+1, edges, E, sol, card, bestSol, bestWt, G, search);
    }
}
void generaGraphToDag(GRAPH G){
    EDGE *edges = GRAPHedges(G);
    int V = GRAPHgetV(G);
    int E = GRAPHgetE(G);
    int lim = E - (V-1);
    if(lim <= 0) return;
    int search = 1;
    int i, j;
    int *sol;
    int *bestsol = calloc(lim, sizeof(int));
    int bestWt = INT_MIN;
    for(i = 1; i <= lim && search; i++){
        sol = malloc(sizeof(int)*i);
        printf("Genero insiemi di archi con dimensione %d\n", i);
        generaR(0, 0, edges, E, sol, i, bestsol, &bestWt, G, &search);
        free(sol);
    }

    printf("Elenco archi rimossi:\n");
    for(j = 0; j < i-1; j++){
        EDGEstore(G, edges[bestsol[j]], stdout);
        GRAPHremoveE(G, edges[bestsol[j]]);
    }
}