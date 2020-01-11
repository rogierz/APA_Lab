//
// Created by Ruggero Nocera on 10/01/2020.
//

#ifndef APA_LAB_GRAPH_H
#define APA_LAB_GRAPH_H
#include <stdio.h>
#include "ST.h"
typedef struct edge{
    int v;
    int w;
    int wt;
} Edge;
typedef struct graph * GRAPH;
GRAPH GRAPHinit(int V);
void GRAPHfree(GRAPH G);
void GRAPHinsertE(GRAPH G, int id1, int id2, int wt);
void GRAPHprintVertex(GRAPH G);
void GRAPHsetTab(GRAPH G, ST tab);
void GRAPHthreeCompleteSubGMATRIX(GRAPH G, char **vertex);
void GRAPHgenerateLadj(GRAPH G);
void GRAPHprintLadj(GRAPH G);
#endif //APA_LAB_GRAPH_H
