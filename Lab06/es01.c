#include <stdio.h>
#include <stdlib.h>

#define fileName "grafo.txt"

typedef struct{
    int u, v;
} edge;

void stampaVertexCover(int *nodes, int nodesLen, edge * edges, int edgesLen);
void powerset(int pos, int *val, int len, int start, int* sol, edge *edges, int edgesLen);
void validate(int *sol, int len, edge *edges, int edgesLen);

int main(){
    int *nodes;
    edge *edges;
    int nodesLen, edgesLen, i;
    FILE *fp = fopen(fileName, "r");
    if(fp == NULL) return -1;
    fscanf(fp, "%d %d", &nodesLen, &edgesLen);
    nodes = malloc(nodesLen* sizeof(int));
    edges = malloc(edgesLen* sizeof(edge));
    for(i = 0; i < nodesLen; i++){
        nodes[i] = i;
    }
    for(i = 0; i < edgesLen; i++){
        fscanf(fp, "%d %d", &edges[i].u, &edges[i].v);
    }
    fclose(fp);
    stampaVertexCover(nodes, nodesLen, edges, edgesLen);
    free(nodes);
    free(edges);
}

void stampaVertexCover(int *nodes, int nodesLen, edge * edges, int edgesLen){
    int* sol = malloc(nodesLen* sizeof(int));
    powerset(0, nodes, nodesLen, 0, sol, edges, edgesLen);
}

void powerset(int pos, int *val, int len, int start, int *sol, edge *edges, int edgesLen){
    int i;
    if(start >= len){
        if(pos > 0) validate(sol, pos, edges, edgesLen);
        return;
    }
    for(i = start; i < len; i++){
        sol[pos] = val[i];
        powerset(pos+1, val, len, i+1, sol, edges, edgesLen);
    }
    powerset(pos, val, len, len, sol, edges, edgesLen);
}

void validate(int *sol, int len, edge *edges, int edgesLen){
    int i, j;
    int mark[edgesLen];
    int flag = 1;
    for(i = 0; i < edgesLen; i++){
        mark[i] = 0;
    }
    for(i = 0; i < len; i++){
        for(j = 0; j < edgesLen; j++){
            if(sol[i] == edges[j].u || sol[i] == edges[j].v) mark[j] = 1;
        }
    }
    for(i = 0; i < edgesLen; i++) if(mark[i] == 0) flag = 0;

    if(flag) {
        printf("(");
        for (i = 0; i < len; i++) {
            printf("%d", sol[i]);
            if (i < len - 1) printf(", ");
        }
        printf(")\n");
    }
}