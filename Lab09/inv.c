#include "inv.h"

void stat_read(FILE *fp, stat_t *statp){
    stat_t tmp;
    fscanf(fp, "%d %d %d %d %d %d", &tmp.hp, &tmp.mp, &tmp.atk, &tmp.def,
            &tmp.mag, &tmp.spr);
    *statp = tmp;
}
void stat_print(FILE *fp, stat_t *statp, int soglia){
    int *try = (int *)statp;
    const int max = 6;
    int i;
    stat_t tmp;
    for(i = 0; i < max; i++){
        if(try[i] < soglia) try[i] = soglia;
    }
    tmp = *statp;
    fprintf(fp, "%d %d %d %d %d %d\n", tmp.hp, tmp.mp, tmp.atk, tmp.def,
           tmp.mag, tmp.spr);

}
void inv_read(FILE *fp, inv_t *invp){
    inv_t tmp;
    fscanf(fp, "%s %s ", tmp.nome, tmp.tipo);
    stat_read(fp, &(tmp.stat));
    *invp = tmp;
}
void inv_print(FILE *fp, inv_t *invp) {
    inv_t tmp = *invp;
    fprintf(fp, "%s %s ", tmp.nome, tmp.tipo);
    stat_print(fp, &tmp.stat, 1);
}

stat_t inv_getStat(inv_t *invp){
    return invp->stat;
}