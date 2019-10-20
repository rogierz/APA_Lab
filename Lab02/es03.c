//
// Created by Ruggero Nocera on 20/10/2019.
//

#include <stdio.h>
#include <string.h>

#define fileNameSequenze "sequenze.txt"
#define fileNameTesto "testo.txt"
#define MAXLEN 5+1
#define MAXSEQ 20
#define MAXWORD 25
int main(){
    FILE *fileSequenze, *fileTesto;
    char sequenze[MAXSEQ][MAXLEN];
    char parola[MAXWORD];
    int i, pos = 1, numSeq, occ;

    fileSequenze = fopen(fileNameSequenze, "r");
    fileTesto = fopen(fileNameTesto, "r");
    if(fileSequenze == NULL || fileTesto == NULL) return -1;
    fscanf(fileSequenze, "%d", &numSeq);
    for(i = 0; i < numSeq; i++){
        fscanf(fileSequenze, "%s", sequenze[i]);
        occ = 0;
        printf("La sequenza %s e\' contenuta in:\n", sequenze[i]);
        while(fscanf(fileTesto, "%s", parola) == 1){
            if(strstr(parola, sequenze[i]) != NULL){
                occ++;
                if(occ <= 10) printf("\t%s posizione %d\n", parola, pos++);
            }
        }
        printf("Per un totale di %d occorrenze.\n\n", occ);
        rewind(fileTesto);
        pos = 1;
    }

    fclose(fileSequenze);
    fclose(fileTesto);
    return 0;
}