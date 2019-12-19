#include "equipArray.h"

#ifndef MAX_STD
#define MAX_STD 20
#endif

struct equipArray_s{
    int *equip;
    int N;
    int maxN;
};

equipArray_t equipArray_init(){
    equipArray_t x = malloc(sizeof(struct equipArray_s));
    if(x == NULL) return NULL;
    x->equip = malloc(MAX_STD* sizeof(int));
    if(x->equip == NULL){
        free(x);
        return NULL;
    }
    x->maxN = MAX_STD;
    x->N = 0;
    return x;
}
void equipArray_free(equipArray_t equipArray){
    free(equipArray->equip);
    free(equipArray);
}

int equipArray_inUse(equipArray_t equipArray){
    if(equipArray != NULL){
        return equipArray->N;
    }
    return -1;
}

void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray){
    int i;
    for(i = 0; i < equipArray->N; i++){
        invArray_printByIndex(fp, invArray, equipArray->equip[i]);
    }
}
int equipArray_getEquipByIndex(equipArray_t equipArray, int index){
    if(index >= equipArray->N || index < 0) return -1;
    return equipArray->equip[index];
}
void equipArray_update(equipArray_t equipArray, invArray_t invArray){
    if(equipArray->N == equipArray->maxN){
        equipArray->equip = realloc(equipArray->equip, equipArray->maxN+MAX_STD);
    }
    int get, maxN = invArray_maxN(invArray);
    printf("Inserisci (i) da aggiungere: ");
    scanf("%d", &get);
    if(get < 0 || get >= maxN) return;
    equipArray->equip[equipArray->N++] = get;
}
