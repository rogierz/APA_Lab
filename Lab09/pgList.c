#include "pgList.h"

typedef struct node_s* link;

struct node_s{
    pg_t pg;
    link next;
};

struct pgList_s{
    link head;
    int N;
};
link pgList_newNode(pg_t pg, link next){
    link x = malloc(sizeof(struct node_s));
    if(x == NULL) return NULL;
    x->pg = pg;
    x->next = next;
    return x;
}

void pgList_freeNode(link node){
    pg_clean(&(node->pg));
    free(node);
}
pgList_t pgList_init(){
    pgList_t ret = malloc(sizeof(struct pgList_s));
    if(ret == NULL) return NULL;
    ret->head = NULL;
    ret->N = 0;
    return ret;
}
void pgList_free(pgList_t pgList){
    link x, p;
    if(pgList->head == NULL){
        free(pgList);
        return;
    }

    for(x = pgList->head->next, p = pgList->head; x != NULL; p = x, x = x->next){
        pgList_freeNode(p);
    }
    free(pgList);
}
void pgList_insert(pgList_t pgList, pg_t pg){
    pgList->head = pgList_newNode(pg, pgList->head);
}
void pgList_read(FILE *fp, pgList_t pgList){
        pg_t tmp;
        while(pg_read(fp, &tmp) != 0){
            pgList_insert(pgList, tmp);
        }
}
void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray){
    link x;
    for(x = pgList->head; x != NULL; x = x->next){
        pg_print(fp, &(x->pg), invArray);
    }
}

pg_t *pgList_searchByCode(pgList_t pgList, char* cod){
    link x;
    if(pgList->head == NULL) return NULL;
    for(x = pgList->head; x != NULL && strcmp(x->pg.cod, cod) != 0; x = x->next);
    if(x != NULL) return &(x->pg);
}

void pgList_remove(pgList_t pgList, char* cod){
    link x, p;
    if(pgList->head == NULL) return;
    if(strcmp(pgList->head->pg.cod, cod) == 0){
        x = pgList->head->next;
        pgList_freeNode(pgList->head);
        pgList->head = x;
        return;
    }

    for(x = pgList->head->next, p = pgList->head; x != NULL && strcmp(x->pg.cod, cod) != 0; p = x, x = x->next);
    if(x != NULL){
        p->next = x->next;
        pgList_freeNode(x);
    }
}