//
// Created by Ruggero Nocera on 17/01/2020.
//

#ifndef APA_LAB_GRAPH_H
#define APA_LAB_GRAPH_H
#include <stdio.h>

typedef struct graph * GRAPH;

typedef struct edge{
    int v;
    int w;
    int wt;
} EDGE;

GRAPH GRAPHinit(int V);
void GRAPHinsertE(GRAPH G, int id1, int id2, int wt);
void GRAPHremoveE(GRAPH G, EDGE e);
EDGE *GRAPHedges(GRAPH G);
GRAPH GRAPHload(FILE *fp);
void GRAPHstore(GRAPH G, FILE *fp);
void EDGEstore(GRAPH G, EDGE e, FILE *fp);
int GRAPHdfsSearchCycle(GRAPH G);
int GRAPHgetV(GRAPH G);
int GRAPHgetE(GRAPH G);
void DAGmaxPath(GRAPH G, int id);
void GRAPHfree(GRAPH G);
#endif //APA_LAB_GRAPH_H
