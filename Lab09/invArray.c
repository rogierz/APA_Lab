#include "invArray.h"

#ifndef MAX_STD
#define MAX_STD 20
#endif

struct invArray_s{
    inv_t *array;
    int N;
    int maxN;
};

invArray_t invArray_init(){
    invArray_t x = malloc(sizeof(struct invArray_s));
    if(x == NULL) return NULL;
    x->array = malloc(MAX_STD * sizeof(inv_t));
    if(x->array == NULL){
        free(x);
        return NULL;
    }
    x->maxN = MAX_STD;
    x->N = 0;
    return x;
}
void invArray_free(invArray_t invArray){
    if(invArray != NULL){
        free(invArray->array);
        free(invArray);
    }
}

void invArray_read(FILE *fp, invArray_t invArray){
    inv_t tmp;
    inv_t *arrayTmp;
    while(!feof(fp)){
        inv_read(fp, &tmp);
        if(invArray->N == invArray->maxN){
            arrayTmp = realloc(invArray->array, invArray->maxN+MAX_STD);
            if(arrayTmp != NULL){
                invArray->array = arrayTmp;
                invArray->maxN = invArray->maxN+MAX_STD;
            }else{
                return;
            }
        }
        invArray->array[invArray->N++] = tmp;
    }
}

void invArray_print(FILE *fp, invArray_t invArray){
    int i;
    for(i = 0; i < invArray->N; i++){
        printf("%d. ", i);
        inv_print(fp, &(invArray->array[i]));
    }
}

int invArray_maxN(invArray_t invArray){
    return invArray->maxN;
}

inv_t *invArray_getByIndex(invArray_t invArray, int index){
    if(index < 0 || index >= invArray->N) return NULL;
    return &(invArray->array[index]);
}

void invArray_printByIndex(FILE *fp, invArray_t invArray, int index){
    inv_t *tmp = invArray_getByIndex(invArray, index);
    if(tmp == NULL) return;
    inv_print(fp, tmp);
}