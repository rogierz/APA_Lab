//
// Created by Ruggero Nocera on 11/01/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "TITOLO.h"
#include "DATE.h"
#include "QUOT.h"

void fileRead(FILE *fp, LISTtitoli l);
int printMenu();

int main(){
    setbuf(stdout, NULL);
    FILE *fp;
    char buf[50];
    int c;
    float min, max;
    LISTtitoli l = LISTinit();
    TITOLO t;
    while((c = printMenu()) != -1){
        switch(c){
            case 0:
                printf("Inserisci nome file: ");
                scanf("%s", buf);
                fp = fopen(buf, "r");
                fileRead(fp, l);
                fclose(fp);
                break;
            case 1:
                printf("Inserisci codice titolo: ");
                scanf("%s", buf);
                t = LISTsearchTitolo(l, buf);
                if(t == NULL){
                    printf("Non e\' stato possibile trovare il titolo.\n");
                    break;
                }
                TITOLOstore(t, stdout);
                break;
            case 2:
                printf("Inserisci codice titolo: ");
                scanf("%s", buf);
                t = LISTsearchTitolo(l, buf);
                if(t == NULL){
                    printf("Non e\' stato possibile trovare il titolo.\n");
                    break;
                }
                DATA d;
                QUOT q;
                printf("Inserisci data: ");
                d = DATAload(stdin);
                q = TITOLOsearchQuot(t, d);
                if(q.data.gg == -1){
                    printf("Non e\' stato possibile trovare una quotazione per questa data\n");
                    break;
                }
                printf("%s ", TITOLOgetKey(t));
                QUOTstore(q, stdout);
                break;
            case 3:
                printf("Inserisci codice titolo: ");
                scanf("%s", buf);
                t = LISTsearchTitolo(l, buf);
                if(t == NULL){
                    printf("Non e\' stato possibile trovare il titolo.\n");
                    break;
                }
                printf("Inserisci intervallo di date: ");
                DATA d1, d2;
                d1 = DATAload(stdin);
                d2 = DATAload(stdin);
                min = max = 0;
                TITOLOminMaxRange(t, d1, d2, &min, &max);
                printf("Per il titolo selezionato:\n\tmin: %.3f\n\tmax: %.3f\n", min, max);
                break;
            case 4:
                printf("Inserisci codice titolo: ");
                scanf("%s", buf);
                t = LISTsearchTitolo(l, buf);
                if(t == NULL){
                    printf("Non e\' stato possibile trovare il titolo.\n");
                    break;
                }
                min = max = 0;
                TITOLOminmax(t, &min, &max);
                printf("Per il titolo selezionato:\n\tmin: %.3f\n\tmax: %.3f\n", min, max);
                break;
            case 5:
                printf("Inserisci codice titolo: ");
                scanf("%s", buf);
                t = LISTsearchTitolo(l, buf);
                if(t == NULL){
                    printf("Non e\' stato possibile trovare il titolo.\n");
                    break;
                }

                int S;
                printf("Inserisci soglia: ");
                scanf("%d", &S);
                if(S > TITOLObstRatio(t)){
                    TITOLObalanceBst(t);
                }
            default:
                LISTstore(l, stdout);
        }
    }
    return 0;
}
int printMenu(){
    printf("--- Comandi ---\n");
    printf("[1] Leggi file\n");
    printf("[2] Ricerca titolo azionario\n");
    printf("[3] Ricerca quotazione di un titolo in una certa data\n");
    printf("[4] Ricerca quotazione di un titolo in un intervallo di date\n");
    printf("[5] Ricerca quotazione minima e massima di un titolo nel periodo complessivo\n");
    printf("[6] Bilancia albero quotazioni\n");
    printf("[7] Esci\n");
    printf("Inserisci comando: ");
    int c;
    scanf("%d", &c);
    if(c > 0 && c < 7)
        return c-1;
    return -1;
}
void fileRead(FILE *fp, LISTtitoli l){
    int nTitoli;
    int nTr;
    char *codTitolo = malloc(sizeof(char)*20);
    fscanf(fp, "%d", &nTitoli);
    DATA d;
    float val;
    int qta;
    TITOLO t;
    for(int i = 0; i < nTitoli; i++) {
        fscanf(fp, "%s %d", codTitolo, &nTr);
        t = LISTsearchTitolo(l, codTitolo);
        if (t == NULL)
            LISTaddTitolo(l, (t = TITOLOnew(codTitolo)));
        for (int j = 0; j < nTr; j++) {
            d = DATAload(fp);
            fscanf(fp, "%f %d", &val, &qta);
            TITOLOaddTransazione(t, d, val, qta);
        }
    }
}

