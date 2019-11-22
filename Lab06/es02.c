#include <stdio.h>
#include <string.h>
#include "List.h"
#include "Item.h"

typedef enum{
    leggi_cmd, leggi_file, cerca_codice, cancella_codice, cancella_date, stampa, esci, err
} comandi_t;

comandi_t printMenuReadCmd();

int main(){
    setbuf(stdout, NULL);
    LIST myList = LISTinit();
    Item tmp;
    char buffer[200];
    FILE *fp;
    comandi_t cmd;
    data d1, d2;
    while((cmd = printMenuReadCmd()) != esci){
        switch(cmd){
            case leggi_cmd:
                printf("Inserisci elemento: ");
                fgets(buffer, 200, stdin);
                tmp = ITEMscan(buffer);
                if(ITEMcmp(tmp, ITEMnull()) != 0){
                    LISTsortIns(myList, tmp);
                    printf("Elemento acquisito con successo!\n");
                }else{
                    printf("Errore nella lettura dell'elemento.\n");
                }
                break;
            case leggi_file:
                printf("Inserisci nome file: ");
                scanf("%s", buffer);
                fp = fopen(buffer, "r");
                if(fp == NULL){
                    printf("Errore nell'apertura del file.\n");
                    break;
                }
                printf("\n");
                while(fgets(buffer, 200, fp) != NULL){
                    tmp = ITEMscan(buffer);
                    if(ITEMcmp(tmp, ITEMnull()) == 0) {
                        fclose(fp);
                        break;
                    }
                    LISTsortIns(myList, tmp);
                }
                fclose(fp);
                break;
            case cerca_codice:
                printf("Inserisci codice da cercare: ");
                scanf("%s", buffer);
                tmp = LISTsearch(myList, buffer);
                ITEMprint(tmp, stdout);
                break;
            case cancella_codice:
                printf("Inserisci codice da eliminare: ");
                scanf("%s", buffer);
                tmp = LISTdeleteByCode(myList, buffer);
                ITEMprint(tmp, stdout);
                break;
            case cancella_date:
                printf("Inserisci date da eliminare(gg/mm/aaa):");
                scanf("%d/%d/%d %d/%d/%d", &d1.gg, &d1.mm, &d1.aaaa, &d2.gg, &d2.mm, &d2.aaaa);
                d1.dataToInt = d1.gg + d1.mm*31 + d1.aaaa*365;
                d2.dataToInt = d2.gg + d2.mm*31 + d2.aaaa*365;
                while(ITEMcmp((tmp = LISTdeleteFirstByDate(myList, d1, d2)), ITEMnull()) != 0){
                    ITEMprint(tmp, stdout);
                }
                break;
            case stampa:
                printf("Inserisci nome file: ");
                scanf("%s", buffer);
                fp = stdout;
                if(strcmp(buffer, "stdout") != 0){
                    fp = fopen(buffer, "w");
                    if(fp == NULL){
                        printf("Errore nell'apertura del file.\n");
                        break;
                    }
                }
                LISTprint(myList, fp);
                if(fp != stdout) fclose(fp);
                break;
            default:
                printf("Comando errato, riprova\n");
        }
    }
}

comandi_t printMenuReadCmd(){
    int cmd;
    printf("\nOperazioni disponibili:\n");
    printf("1. Acquisisci elemento da console\n");
    printf("2. Acquisisci elementi da file\n");
    printf("3. Ricerca per codice\n");
    printf("4. Cancella per codice\n");
    printf("5. Cancella tra date\n");
    printf("6. Stampa su file\n");
    printf("7. Esci\n");
    printf("Inserisci numero: ");
    scanf("%d", &cmd);
    fflush(stdin);
    if(cmd > err) return err;
    return --cmd;
}