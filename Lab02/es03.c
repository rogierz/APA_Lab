//
// Created by Ruggero Nocera on 20/10/2019.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define fileNameSequenze "sequenze.txt"
#define fileNameTesto "testo.txt"
#define MAXLEN 5+1
#define MAXSEQ 20
#define MAXWORD 25
#define MAXBUF 201
void strToLower(char *str);
void strToAlNum(char *str);

int main(){
    FILE *fileSequenze, *fileTesto;
    char sequenze[MAXSEQ][MAXLEN];
    char parola[MAXWORD];
    char buff[MAXBUF];
    setbuf(stdout, NULL);
    int i, pos = 1, numSeq, occ, offset = 0;
    fileSequenze = fopen(fileNameSequenze, "r");
    fileTesto = fopen(fileNameTesto, "r");
    if(fileSequenze == NULL || fileTesto == NULL) return -1;
    fscanf(fileSequenze, "%d", &numSeq);
    for(i = 0; i < numSeq; i++){
        fscanf(fileSequenze, "%s", sequenze[i]);
        occ = 0;
        printf("La sequenza %s e\' contenuta in:\n", sequenze[i]);
        strToLower(sequenze[i]);
        while(fgets(buff, MAXBUF, fileTesto) != NULL){
            strToAlNum(buff);
            strToLower(buff);
            offset = 0;
            while(sscanf(buff+offset, "%s", parola) == 1){
                offset = strstr(buff+offset, parola) - buff + strlen(parola);
                if(strstr(parola, sequenze[i]) != NULL){
                    occ++;
                    if(occ <= 10) printf("\t%s posizione %d\n", parola, pos);
                }
                pos++;
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

void strToLower(char *str){
    int i;
    for(i = 0; str[i] != '\0'; i++) str[i] = tolower(str[i]);
}

void strToAlNum(char *str){
    int i;
    for(i = 0; str[i] != '\0'; i++) if(!isalnum(str[i])) str[i] = ' ';
}