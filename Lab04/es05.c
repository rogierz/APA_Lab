//
// Created by Ruggero Nocera on 04/11/2019.
//

//
// Created by Ruggero Nocera on 04/11/2019.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 30
#define MAXENTRIES 1000
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
void doCmd(Entry *entries[][MAXENTRIES], int len, comando_e cmd);
int leggiFile(char *nomeFile, Entry entries[MAXENTRIES], Entry *ordinato[][MAXENTRIES]);
void stampaOccorrenza(Entry entry, FILE* stream);
void ordinaData(Entry *entries[MAXENTRIES], int len);
void ordinaTratta(Entry *entries[MAXENTRIES], int len);
void ordinaPartenza(Entry *entries[MAXENTRIES], int len);
void ordinaArrivo(Entry *entries[MAXENTRIES], int len);
void cerca(Entry *entries[MAXENTRIES], int len);

int main(){
    setbuf(stdout, NULL);
    Entry entries[MAXENTRIES];
    Entry *ordinato[r_ordina_arrivo][MAXENTRIES];
    int numEntry;
    comando_e comando;
    numEntry = leggiFile(fileName, entries, ordinato);
    if(numEntry == -1) return -1;
    while((comando = leggiComando()) != r_fine){
        doCmd(ordinato, numEntry, comando);
    }
    return 0;
}

int leggiFile(char *nomeFile, Entry entries[MAXENTRIES], Entry *ordinato[][MAXENTRIES]){
    FILE* logFile = fopen(nomeFile, "r");
    if(logFile == NULL) return -1;
    int numEntry = 0, i, j;
    fscanf(logFile, "%d", &numEntry);
    for(i = 0; i < numEntry; i++){
        fscanf(logFile, "%s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d", entries[i].id, entries[i].partenza, entries[i].destinazione, &entries[i].data.aaaa, &entries[i].data.mm,
               &entries[i].data.gg, &entries[i].oraPartenza.hh, &entries[i].oraPartenza.mm, &entries[i].oraPartenza.ss, &entries[i].oraPartenza.hh,
               &entries[i].oraPartenza.mm, &entries[i].oraPartenza.ss, &entries[i].ritardo);
        entries[i].data.dataToInt = entries[i].data.gg + entries[i].data.mm*31 + entries[i].data.aaaa*365;
        entries[i].oraPartenza.oraToInt = entries[i].oraPartenza.hh*3600 + entries[i].oraPartenza.mm*60 + entries[i].oraPartenza.ss;
        entries[i].oraArrivo.oraToInt = entries[i].oraArrivo.hh*3600 + entries[i].oraArrivo.mm*60 + entries[i].oraArrivo.ss;
        for(j = 0; j < r_ordina_arrivo; j++) ordinato[j][i] = &entries[i];
    }
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

void doCmd(Entry *entries[][MAXENTRIES], int len, comando_e cmd){
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
                    printf("Ordinato per %s:\n", ordinamenti[j]);
                    for (i = 0; i < len; i++) stampaOccorrenza(*entries[j][i], stdout);
                    printf("\n");
                }
            }else{
                fp = fopen(buff, "w");
                if(fp == NULL){
                    printf("Non posso aprire il file.");
                }else{
                    for(j = 0; j < r_ordina_arrivo; j++) {
                        printf("Ordinato per %s:\n", ordinamenti[j]);
                        for (i = 0; i < len; i++) stampaOccorrenza(*entries[j][i], fp);
                        printf("\n");
                    }
                    fclose(fp);
                }
            }
            printf("\n");
            break;
        case r_ordina_data:
            ordinaData(entries[0], len);
            break;
        case r_ordina_tratta:
            ordinaTratta(entries[1], len);
            break;
        case r_ordina_partenza:
            ordinaPartenza(entries[2], len);
            break;
        case r_ordina_arrivo:
            ordinaArrivo(entries[3], len);
            break;
        case r_cerca:
            cerca(entries[2], len);
            break;
        default:
            printf("Comando errato, riprovare!\n");
    }
}

void ordinaData(Entry *entries[MAXENTRIES], int len){
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
void ordinaTratta(Entry *entries[MAXENTRIES], int len){
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

void ordinaPartenza(Entry *entries[MAXENTRIES], int len){
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
void ordinaArrivo(Entry *entries[MAXENTRIES], int len){
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
void cerca(Entry* entries[MAXENTRIES], int len){
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