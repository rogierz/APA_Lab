#include <stdio.h>
#include <stdlib.h>

#define fileName "grafo.txt"

typedef struct{
    int u, v;
} edge;

void stampaVertexCover(int *nodes, int nodesLen, edge * edges, int edgesLen);

//void generateDeT(int pos, int *val, int len, int start, int* sol, edge *edges, int edgesLen);
void generateDR(int pos, int* val, int len, int* sol, edge *edges, int edgesLen);

void validateDeT(int *sol, int len, edge *edges, int edgesLen); //O(N^2)
void validateDR(int *sol, int len, edge *edges, int edgesLen); //O(N)
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
    int* sol = calloc(nodesLen, sizeof(int));
    //generateDeT(0, nodes, nodesLen, 0, sol, edges, edgesLen);
    generateDR(0, nodes, nodesLen, sol, edges, edgesLen);
}

void generateDR(int pos, int *val, int len, int *sol, edge *edges, int edgesLen){

    if(pos >= len){
        validateDR(sol, len, edges, edgesLen);
        return;
    }
    sol[pos] = 0;
    generateDR(pos+1, val, len, sol, edges, edgesLen);
    sol[pos] = 1;
    generateDR(pos+1, val, len, sol, edges, edgesLen);
}

void validateDR(int *sol, int len, edge *edges, int edgesLen){
    int i;
    int flag = 1;
    int firstPrinted = 0;
    for(i = 0; i < edgesLen; i++){
        if(sol[edges[i].u] == 0 && sol[edges[i].v] == 0) flag = 0;
    }
    if(flag) {
        printf("(");
        for (i = 0; i < len; i++) {
            if(sol[i] == 1){
                if (firstPrinted == 1) printf(", ");
                printf("%d", i);
                firstPrinted = 1;
            }
        }
        printf(")\n");
    }
}
/*void generateDeT(int pos, int *val, int len, int start, int *sol, edge *edges, int edgesLen){
    int i;
    if(start >= len){
        if(pos > 0) validateDeT(sol, pos, edges, edgesLen);
        return;
    }
    for(i = start; i < len; i++){
        sol[pos] = val[i];
        generateDeT(pos+1, val, len, i+1, sol, edges, edgesLen);
    }
    generateDeT(pos, val, len, len, sol, edges, edgesLen);
}*/

void validateDeT(int *sol, int len, edge *edges, int edgesLen){
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