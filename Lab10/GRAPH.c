//
// Created by Ruggero Nocera on 10/01/2020.
//

#include "GRAPH.h"
#include "ST.h"
#include <stdlib.h>
#include <string.h>
typedef struct node *link;
struct graph{
    int V;
    int E;
    int **madj;
    link* ladj;
    link z;
    ST tab;
};
struct node{
    int v;
    link next;
};

static int **MATRIXint(int r, int c, int val){
    int i, j;
    int **ret = malloc(sizeof(int *)*r);
    for(i = 0; i < r; i++){
        ret[i] = malloc(sizeof(int)*c);
        for(j = 0; j < c; j++) ret[i][j] = val;
    }
    return ret;
}
static link NEWnode(int v, link next){
    link x = malloc(sizeof(*x));
    x->v = v;
    x->next = next;
    return x;
}
static Edge EDGEcreate(int v, int w, int wt){
    Edge e;
    e.v = v;
    e.w = w;
    e.wt = wt;
    return e;
}

GRAPH GRAPHinit(int V){
    GRAPH G = malloc(sizeof(*G));
    G->V = V;
    G->E = 0;
    G->madj = MATRIXint(V, V, 0);
    G->ladj = malloc(sizeof(*G->ladj)*V);
    G->z = NEWnode(-1, NULL);
    for(int i = 0; i < G->V; i++)
        G->ladj[i] = G->z;
    G->tab = STinit(V);
    return G;
}

void GRAPHfree(GRAPH G){
    STfree(G->tab);
    for(int i = 0; i < G->V; i++)
        free(G->madj[i]);
    free(G->madj);
    free(G);
}

static void insertE(GRAPH G, Edge e){
    int v = e.v;
    int w = e.w;
    int wt = e.wt;
    if(G->madj[v][w] != 0) G->E++;
    G->madj[v][w] = wt;
    G->madj[w][v] = wt;
}
void GRAPHinsertE(GRAPH G, int id1, int id2, int wt){
    insertE(G, EDGEcreate(id1, id2, wt));
}

static void merge(char **vett, char **tmp, int l, int m, int r){
    int i, j, k;
    i = l;
    j = m+1;
    for(k = l; k <= r; k++){
        if(i > m){
            tmp[k] = vett[j++];
        } else if (j > r){
            tmp[k] = vett[i++];
        } else if (strcmp(vett[i], vett[j]) <= 0){
            tmp[k] = vett[i++];
        } else {
            tmp[k] = vett[j++];
        }
    }
    for(k = l; k <= r; k++){
        vett[k] = tmp[k];
    }
}
static void mergeSortR(char **vett, char **tmp, int l, int r){
    int m = (l+r)/2;
    if(l >= r) return;
    mergeSortR(vett, tmp, l, m);
    mergeSortR(vett, tmp, m+1, r);
    merge(vett, tmp, l, m, r);
}
static void mergeSort(char **vett, int n){
    char **tmp = malloc(sizeof(char *)*n);
    mergeSortR(vett, tmp, 0, n-1);
    free(tmp);
}
void GRAPHprintVertex(GRAPH G){
    int n = G->V;
    int m = (G->V-1);
    int t = 0;
    int i = 0;
    int k;
    char **vertexNames = malloc(sizeof(char *)*n);
    char **archiIncidenti = malloc(sizeof(char *)*m);
    for(i = 0; i < n; i++)
        vertexNames[i] = strdup(STsearchByIndex(G->tab, i));
    mergeSort(vertexNames, n);
    for(i = 0; i < n; i++){
        t = 0;
        printf("Nome del vertice: %s\n", vertexNames[i]);
        int realIndex = STsearch(G->tab, vertexNames[i]);
        for(k = 0; k < G->V; k++){
                if(G->madj[realIndex][k] != 0) archiIncidenti[t++] = strdup(STsearchByIndex(G->tab, k));
        }
        mergeSort(archiIncidenti, t);
        printf("\tArchi incidenti:\n");
        for(k = 0; k < t; k++){
            printf("\t--- %s\n", archiIncidenti[k]);
            free(archiIncidenti[k]);
        }
    }
}

void GRAPHsetTab(GRAPH G, ST tab){
    STfree(G->tab);
    G->tab = tab;
    return;
}

void GRAPHthreeCompleteSubGMATRIX(GRAPH G, char **vertex){
    int i = 0;
    const int n = 3;
    int ad = 1;
    int v[3];
    for(i = 0; i < n; i++){
        v[i] = STsearch(G->tab, vertex[i]);
    }
    for(i = 0; i < n; i++){
        if(G->madj[v[i]][v[(i+1)%n]] == 0)
            ad = 0;
    }
    if(ad == 0){
        printf("I tre vertici non formano un sottografo completo.\n");
    }else{
        printf("I tre vertici formano un sottografo completo.\n");
    }
}

void GRAPHgenerateLadj(GRAPH G){
    int V = G->V;
    int i, j;
    for(i = 0; i < V; i++){
        for(j = i+1; j < V; j++){
            if(G->madj[i][j] != 0){
                G->ladj[i] = NEWnode(j, G->ladj[i]);
                G->ladj[j] = NEWnode(i, G->ladj[j]);
            }
        }
    }
}

void GRAPHprintLadj(GRAPH G){
    int i;
    link x;
    for(i = 0; i < G->V; i++){
        printf("%s ", STsearchByIndex(G->tab, i));
        for(x = G->ladj[i]; x != G->z; x = x->next){
            printf("-> %s", STsearchByIndex(G->tab, x->v));
        }
        printf("\n");
    }
}