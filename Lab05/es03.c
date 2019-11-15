//
// Created by Ruggero Nocera on 10/11/2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 30
#define fileName "log.txt"

struct data{
    int gg;
    int mm;
    int aaaa;
    int dataToInt;
};

struct ora{
    int hh;
    int mm;
    int ss;
    int oraToInt;
};

typedef struct{
    char id[MAX];
    char partenza[MAX];
    char destinazione[MAX];
    struct data data;
    struct ora oraPartenza;
    struct ora oraArrivo;
    int ritardo;
} Entry;
typedef enum{
    r_stampa, r_ordina_data, r_ordina_tratta, r_ordina_partenza, r_ordina_arrivo, r_cerca, r_fine, r_err
} comando_e;

void strToLower(char *str);
comando_e leggiComando();
void doCmd(Entry ***entries, int len, comando_e cmd);
int leggiFile(char *nomeFile, Entry **entries, Entry ****ordinato);
void stampaOccorrenza(Entry entry, FILE* stream);
void ordinaData(Entry **entries, int len);
void ordinaTratta(Entry **entries, int len);
void ordinaPartenza(Entry **entries, int len);
void ordinaArrivo(Entry **entries, int len);
void cerca(Entry **entries, int len);

int ordFlag[r_ordina_arrivo];

int main(){
    int i;
    setbuf(stdout, NULL);
    Entry *entries;
    Entry ***ordinato;
    int numEntry;
    for(i = 0; i < r_ordina_arrivo; i++) ordFlag[i] = 0;

    comando_e comando;
    numEntry = leggiFile(fileName, &entries, &ordinato);
    if(numEntry == -1) return -1;

    while((comando = leggiComando()) != r_fine){
        doCmd(ordinato, numEntry, comando);
    }
    return 0;
}

int leggiFile(char *nomeFile, Entry **entries, Entry ****ordinato){
    FILE* logFile = fopen(nomeFile, "r");
    Entry * tmp;
    if(logFile == NULL) return -1;
    int numEntry = 0, i, j;
    fscanf(logFile, "%d", &numEntry);
    tmp = malloc(numEntry* sizeof(Entry));
    *ordinato = malloc(sizeof(Entry **) * r_ordina_arrivo);
    if(*entries == NULL || *ordinato == NULL) return -1;
    for(i = 0; i < r_ordina_arrivo; i++){
        (*ordinato)[i] = malloc(sizeof(Entry *) * numEntry);
        if((*ordinato)[i] == NULL) return -1;
    }
    for(i = 0; i < numEntry; i++){
        fscanf(logFile, "%s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d", tmp[i].id, tmp[i].partenza, tmp[i].destinazione, &tmp[i].data.aaaa, &tmp[i].data.mm,
               &tmp[i].data.gg, &tmp[i].oraPartenza.hh, &tmp[i].oraPartenza.mm, &tmp[i].oraPartenza.ss, &tmp[i].oraPartenza.hh,
               &tmp[i].oraPartenza.mm, &tmp[i].oraPartenza.ss, &tmp[i].ritardo);
        tmp[i].data.dataToInt = tmp[i].data.gg + tmp[i].data.mm*31 + tmp[i].data.aaaa*365;
        tmp[i].oraPartenza.oraToInt = tmp[i].oraPartenza.hh*3600 + tmp[i].oraPartenza.mm*60 + tmp[i].oraPartenza.ss;
        tmp[i].oraArrivo.oraToInt = tmp[i].oraArrivo.hh*3600 + tmp[i].oraArrivo.mm*60 + tmp[i].oraArrivo.ss;
        for(j = 0; j < r_ordina_arrivo; j++) (*ordinato)[j][i] = &tmp[i];
    }
    *entries = tmp;
    fclose(logFile);
    return numEntry;
}

comando_e leggiComando(){
    comando_e c;
    char *cmdTable[r_err] = {"stampa", "ordina_data", "ordina_tratta", "ordina_partenza", "ordina_arrivo", "cerca", "fine"};
    char cmd[MAX];
    printf("Comando (stampa/ordina_data/ordina_tratta/ordina_partenza/ordina_arrivo/cerca): ");
    scanf("%s", cmd);
    strToLower(cmd);
    c = r_stampa;
    while(c < r_err && strcmp(cmd, cmdTable[c]) != 0){
        c++;
    }
    return c;
}

void doCmd(Entry ***entries, int len, comando_e cmd){
    FILE* fp;
    char buff[MAX];
    char *ordinamenti[r_ordina_arrivo] = {"data", "tratta", "partenza", "arrivo"};

    int i, j;
    switch(cmd) {
        case r_stampa:
            printf("Dove vuoi stampare? (stdout o nomeFile): ");
            scanf("%s", buff);
            if (strcmp(buff, "stdout") == 0){
                for(j = 0; j < r_ordina_arrivo; j++) {
                    if(ordFlag[j] == 1){
                        printf("Ordinato per %s:\n", ordinamenti[j]);
                        for (i = 0; i < len; i++) stampaOccorrenza(*entries[j][i], stdout);
                        printf("\n");
                    }
                }
            }else{
                fp = fopen(buff, "w");
                if(fp == NULL){
                    printf("Non posso aprire il file.");
                }else{
                    for(j = 0; j < r_ordina_arrivo; j++) {
                        if(ordFlag[j] == 1){
                            printf("Ordinato per %s:\n", ordinamenti[j]);
                            for (i = 0; i < len; i++) stampaOccorrenza(*entries[j][i], fp);
                            printf("\n");
                        }
                    }
                    fclose(fp);
                }
            }
            printf("\n");
            break;
        case r_ordina_data:
            ordFlag[0] = 1;
            ordinaData(entries[0], len);
            break;
        case r_ordina_tratta:
            ordFlag[1] = 1;
            ordinaTratta(entries[1], len);
            break;
        case r_ordina_partenza:
            ordFlag[2] = 1;
            ordinaPartenza(entries[2], len);
            break;
        case r_ordina_arrivo:
            ordFlag[3] = 1;
            ordinaArrivo(entries[3], len);
            break;
        case r_cerca:
            cerca(entries[2], len);
            break;
        default:
            printf("Comando errato, riprovare!\n");
    }
}

void ordinaData(Entry **entries, int len){
    int i, j;
    Entry *tmp;
    for(i = 1; i < len; i++){
        tmp = entries[i];
        for(j = i-1; j >= 0 && tmp->data.dataToInt < entries[j]->data.dataToInt; j--){
            entries[j+1] = entries[j];
        }
        entries[j+1] = tmp;
    }
}
void ordinaTratta(Entry **entries, int len){
    int i, j;
    Entry *tmp;
    for(i = 1; i < len; i++){
        tmp = entries[i];
        for(j = i-1; j >= 0 && strcmp(tmp->id, entries[j]->id) < 0; j--){
            entries[j+1] = entries[j];
        }
        entries[j+1] = tmp;
    }
}

void ordinaPartenza(Entry **entries, int len){
    int i, j;
    Entry *tmp;
    for(i = 1; i < len; i++){
        tmp = entries[i];
        for(j = i-1; j >= 0 && strcmp(tmp->partenza, entries[j]->partenza) < 0; j--){
            entries[j+1] = entries[j];
        }
        entries[j+1] = tmp;
    }
}
void ordinaArrivo(Entry **entries, int len){
    int i, j;
    Entry *tmp;
    for(i = 1; i < len; i++){
        tmp = entries[i];
        for(j = i-1; j >= 0 && strcmp(tmp->destinazione, entries[j]->destinazione) < 0; j--){
            entries[j+1] = entries[j];
        }
        entries[j+1] = tmp;
    }
}
void cerca(Entry** entries, int len){
    int m, l, r;
    char buff[MAX];
    printf("Inserisci stazione da cercare: ");
    scanf("%s", buff);
    l = 0;
    r = len-1;
    while(l <= r){
        m = (l+r)/2;
        if(strcmp(entries[m]->partenza, buff) == 0){
            stampaOccorrenza(*entries[m], stdout);
            break;
        }
        if(strcmp(entries[m]->partenza, buff) < 0){
            l = m+1;
        }else{
            r = m-1;
        }
    }
}
void stampaOccorrenza(Entry entry, FILE* stream){
    fprintf(stream, "%s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d\n", entry.id, entry.partenza, entry.destinazione,
            entry.data.gg, entry.data.mm, entry.data.aaaa,
            entry.oraPartenza.hh, entry.oraPartenza.mm, entry.oraPartenza.ss,
            entry.oraArrivo.hh, entry.oraArrivo.mm, entry.oraArrivo.ss, entry.ritardo);
}

void strToLower(char *str){
    int i;
    for(i = 0; str[i] != '\0'; i++) str[i] = tolower(str[i]);
}
