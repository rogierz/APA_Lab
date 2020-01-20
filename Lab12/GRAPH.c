//
// Created by Ruggero Nocera on 17/01/2020.
//

#include "GRAPH.h"
#include "ST.h"
#include <stdlib.h>
#include <stdio.h>
#define MAXC 30
#define NO_EDGE -1
struct graph{
    int V;
    int E;
    int **madj;
    ST st;
};

static EDGE EDGEcreate(int id1, int id2, int wt){
    EDGE e;
    e.v = id1;
    e.w = id2;
    e.wt = wt;
    return e;
}

GRAPH GRAPHinit(int V){
    GRAPH G = malloc(sizeof(struct graph));
    G->V = V;
    G->E = 0;
    int i, j;
    G->madj = malloc(sizeof(int *)*V);
    for(i = 0; i < V; i++){
        G->madj[i] = malloc(sizeof(int)*G->V);
        for(j = 0; j < G->V; j++){
            G->madj[i][j] = NO_EDGE;
        }
    }
    G->st = STinit(G->V);
}

GRAPH GRAPHload(FILE *fp){
    int V, id1, id2, wt;
    char label1[MAXC], label2[MAXC];
    fscanf(fp, "%d", &V);
    GRAPH G = GRAPHinit(V);
    for(int i = 0; i < G->V; i++){
        fscanf(fp, "%s", label1);
        STinsert(G->st, label1);
    }
    while(!feof(fp)){
        fscanf(fp, "%s %s %d", label1, label2, &wt);
        id1 = STsearch(G->st, label1);
        id2 = STsearch(G->st, label2);
        if(id1 >= 0 && id2 >= 0)
            GRAPHinsertE(G, id1, id2, wt);
    }
    return G;
}
void GRAPHstore(GRAPH G, FILE *fp){
    fprintf(fp, "%d\n", G->V);
    for(int i = 0; i < G->V; i++)
        fprintf(fp, "%s\n", STsearchByIndex(G->st, i));
    for(int i = 0; i < G->V; i++)
        for(int j = 0; j < G->V; j++)
            if(G->madj[i][j] != NO_EDGE)
                fprintf(fp, "%s %s %d\n", STsearchByIndex(G->st, i), STsearchByIndex(G->st, j), G->madj[i][j]);
}
static void insertE(GRAPH G, EDGE e){
    if(G->madj[e.v][e.w] == NO_EDGE) G->E++;
    G->madj[e.v][e.w] = e.wt;
}

void GRAPHinsertE(GRAPH G, int id1, int id2, int wt){
    insertE(G, EDGEcreate(id1, id2, wt));
}

void GRAPHremoveE(GRAPH G, EDGE e){
    if(G->madj[e.v][e.w] == NO_EDGE) G->E--;
    G->madj[e.v][e.w] = NO_EDGE;
}

static int dfsR(GRAPH G, EDGE e, int *pre, int *post, int *time){
    int v, ret = 0;
    pre[e.w] = (*time)++;
    for(v = 0; v < G->V && !ret; v++){
        if(G->madj[e.w][v] != NO_EDGE){
            if(pre[v] == -1){
                ret = dfsR(G, EDGEcreate(e.w, v, 0), pre, post, time);
            }else{
                if(post[v] == -1)
                    ret = 1;
            }
        }
    }
    post[e.w] = (*time)++;
    return ret;
}
int GRAPHdfsSearchCycle(GRAPH G){
    int *pre, *post;
    int time = 0;
    pre = malloc(sizeof(int)*G->V);
    post = malloc(sizeof(int)*G->V);
    for(int i = 0; i < G->V; i++)
        pre[i] = post[i] = -1;
    for(int v = 0; v < G->V; v++){
        if(pre[v] == -1)
            if(dfsR(G, EDGEcreate(v, v, 0), pre, post, &time)){
                free(pre);
                free(post);
                return 1;
            }
    }
    free(pre);
    free(post);
    return 0;
}

int GRAPHgetV(GRAPH G){
    return G->V;
}

int GRAPHgetE(GRAPH G){
    return G->E;
}
EDGE *GRAPHedges(GRAPH G){
    int k = 0;
    EDGE *a = malloc(sizeof(struct edge)*G->E);
    int i = 0;
    int j = 0;
    for(i = 0; i < G->V; i++){
        for(j = 0; j < G->V; j++)
            if(G->madj[i][j] != NO_EDGE)
                a[k++] = EDGEcreate(i, j, G->madj[i][j]);
    }
    return a;
}

void EDGEstore(GRAPH G, EDGE e, FILE *fp){
    fprintf(fp, "%s %s %d\n", STsearchByIndex(G->st, e.v), STsearchByIndex(G->st, e.w), e.wt);
}

static void TSdfsR(GRAPH G, int v, int w, int *pre, int *ts, int *time){
    pre[w] = v;
    for(int i = 0; i < G->V; i++){
        if(G->madj[w][i] != -1)
            if(pre[i] == -1)
                TSdfsR(G, w, i, pre, ts, time);
    }
    ts[(*time)++] = w;
}

static int parent(int *id, int i){
    if(id[i] == i) return i;
    return parent(id, id[i]);
}
void DAGmaxPath(GRAPH G, int id){
    int *pre = malloc(sizeof(int)*G->V);
    int *ts = malloc(sizeof(int)*G->V);
    int time = 0;
    int i;
    for(i = 0; i < G->V; i++){
        pre[i] = ts[i] = -1;
    }
    TSdfsR(G, id, id, pre, ts, &time);
    for(i = 0; i < G->V; i++)
        if(pre[i] == -1)
            TSdfsR(G, i, i, pre, ts, &time);

    int *d = malloc(sizeof(int)*G->V);
    for(i = 0; i < G->V; i++){
        d[i] = 0;
    }
    for(i = time-1; i >= 0; i--){
        for(int v = 0; v < G->V; v++){
            if(G->madj[ts[i]][v] != -1 && parent(pre, v) == id && parent(pre, ts[i]) == id){
                if(d[ts[i]] + G->madj[ts[i]][v] > d[v]){
                    d[v] = d[ts[i]] + G->madj[ts[i]][v];
                }
            }
        }
    }
    printf("Partendo dal nodo %s: (i nodi irraggiungibili non vengono mostrati)\n", STsearchByIndex(G->st, id));
   for(i = 0; i < time; i++){
       if(d[ts[i]] != 0)
           printf("\t%s %d\n", STsearchByIndex(G->st, ts[i]), d[ts[i]]);
    }
    free(ts);
    free(pre);
}
void GRAPHfree(GRAPH G){
    int i;
    for(i = 0; i < G->V; i++)
        free(G->madj[i]);
    free(G->madj);
    free(G->st);
    free(G);
}