#include "pg.h"

int pg_read(FILE *fp, pg_t *pgp){
    int ret = 0;
    pg_t tmp;
    tmp.equip = equipArray_init();
    if(fscanf(fp, "%s %s %s %d %d %d %d %d %d", tmp.cod, tmp.nome, tmp.classe, &(tmp.b_stat.hp), &(tmp.b_stat.mp),
              &(tmp.b_stat.atk), &(tmp.b_stat.def), &(tmp.b_stat.mag), &(tmp.b_stat.spr)) == 9){
        ret = 1;
        *pgp = tmp;
    }
    return ret;
}
void pg_clean(pg_t *pgp){
    equipArray_free(pgp->equip);
}
void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray){
    pg_t tmp = *pgp;
    fprintf(fp, "%s %s %s %d %d %d %d %d %d\n", tmp.cod, tmp.nome, tmp.classe, tmp.b_stat.hp, tmp.b_stat.mp,
           tmp.b_stat.atk, tmp.b_stat.def, tmp.b_stat.mag, tmp.b_stat.spr);
    equipArray_print(fp, tmp.equip, invArray);
}

void pg_updateEquip(pg_t *pgp, invArray_t invArray){
    equipArray_update(pgp->equip, invArray);
}