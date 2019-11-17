#include "Item.h"

Item ITEMscan(char *s){
    Item tmp;
    if(sscanf(s, "%s %s %s %d/%d/%d %s %s %d", tmp.codice, tmp.nome, tmp.cognome, &tmp.nascita.gg, &tmp.nascita.mm,
            &tmp.nascita.aaaa, tmp.via, tmp.citta, &tmp.cap) != 9)
        return ITEMnull();
    tmp.nascita.dataToInt = tmp.nascita.gg + tmp.nascita.mm*31 + tmp.nascita.aaaa*365;
    return tmp;
}

void ITEMprint(Item tmp, FILE* fp){
    fprintf(fp, "%s %s %s %02d/%02d/%04d %s %s %d\n", tmp.codice, tmp.nome, tmp.cognome, tmp.nascita.gg, tmp.nascita.mm, tmp.nascita.aaaa, tmp.via, tmp.citta, tmp.cap);
}

int ITEMcmp (Item a1, Item a2){
    return a2.nascita.dataToInt-a1.nascita.dataToInt;
}

Item ITEMnull(){
    Item tmp;
    tmp.nascita.dataToInt = -1;
    return tmp;
}
