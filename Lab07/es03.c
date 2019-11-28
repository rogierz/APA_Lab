#include <stdio.h>
#include "PG.h"
#include "LISTPG.h"
#include "INV.h"

typedef enum{
     e_caricap, e_caricao, e_addp, e_remp, e_addop, e_remop, e_stampa, e_fine,  e_err
} cmd;

cmd printMenuAndGetCmd();

int main(){
    setbuf(stdout, NULL);
    LISTPG myList = LISTPGinit();
    TABINV myInv = NULL;
    FILE *fpersonaggi = fopen("pg.txt", "r");
    FILE *finv = fopen("inventario.txt", "r");
    PG tmpPG;
    INV tmpINV;
    char buff[MAXNAME*5];
    int i, tmp;
    cmd c;
    while((c = printMenuAndGetCmd()) != e_fine){
        switch(c){
            case e_caricap:
                while(fgets(buff, MAXNAME*5, fpersonaggi) != NULL){
                    tmpPG = PGscan(buff);
                    LISTPGSortedIns(myList, tmpPG);
                }
                break;
            case e_caricao:
                fscanf(finv, "%d%*c", &tmp);
                myInv = TABINVinit(tmp);
                for(i = 0; i < tmp; i++){
                    fgets(buff, MAXNAME*5, finv);
                    tmpINV = INVscan(buff);
                    TABINVadd(myInv, tmpINV);
                }
                break;
            case e_addp:
                fflush(stdin);
                fgets(buff, MAXNAME*5, stdin);
                tmpPG = PGscan(buff);
                LISTPGSortedIns(myList, tmpPG);
                break;
            case e_remp:
                printf("Inserisci codice del personaggio da rimuovere: ");
                scanf("%s", buff);
                LISTPGdelete(myList, buff);
                break;
            case e_addop:
                printf("Inserisci nome dell'oggetto e codice del personaggio: ");
                scanf("%s", buff);
                tmpINV = TABINVget(myInv, buff);
                if(tmpINV == NULL){
                    printf("Oggetto non trovato.\n");
                    break;
                }
                scanf("%s", buff);
                tmpPG = LISTPGsearch(myList, buff);
                if(PGcmp(tmpPG, PGnull()) == 0){
                    printf("Personaggio non trovato.\n");
                    break;
                }
                PGaddINV(tmpPG, tmpINV);
                break;
            case e_remop:
                printf("Inserisci nome dell'oggetto e codice del personaggio: ");
                scanf("%s", buff);
                tmpINV = TABINVget(myInv, buff);
                if(tmpINV == NULL){
                    printf("Oggetto non trovato.\n");
                    break;
                }
                scanf("%s", buff);
                tmpPG = LISTPGsearch(myList, buff);
                if(PGcmp(tmpPG, PGnull()) == 0){
                    printf("Personaggio non trovato.\n");
                    break;
                }
                PGremoveINV(tmpPG, tmpINV);
                break;
            case e_stampa:
                LISTPGprint(myList, stdout);
                printf("\n\n");
                if(myInv != NULL) TABINVprint(myInv, stdout);
                break;
            default:
                break;
        }
    }
    LISTPGfree(myList);
    TABINVfree(myInv);
    fclose(fpersonaggi);
    fclose(finv);
    return 0;
}

cmd printMenuAndGetCmd(){
    int i;
    do{
    printf("\n1. Carica personaggi\n");
    printf("2. Carica oggetti\n");
    printf("3. Aggiungi personaggio\n");
    printf("4. Elimina un personaggio\n");
    printf("5. Aggiungi oggetto ad un personaggio\n");
    printf("6. Rimuovi oggetto ad un personaggio\n");
    printf("7. Stampa personaggi e oggetti\n");
    printf("8. Esci\n");
    printf("Inserisci [n]: ");

    scanf("%d", &i);
    i--;
    }while(i == e_err);
    return i;
}