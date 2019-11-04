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
void doCmd(Entry *entries, int len, comando_e cmd, comando_e lastCmd);
int leggiFile(char *nomeFile, Entry entries[MAXENTRIES]);
void stampaOccorrenza(Entry entry, FILE* stream);
void ordinaData(Entry entries[MAXENTRIES], int len);
void ordinaTratta(Entry entries[MAXENTRIES], int len);
void ordinaPartenza(Entry entries[MAXENTRIES], int len);
void ordinaArrivo(Entry entries[MAXENTRIES], int len);
void cerca(Entry entries[MAXENTRIES], int len, comando_e lastCmd);

int main(){
    setbuf(stdout, NULL);
    Entry entries[MAXENTRIES];
    int numEntry;
    comando_e comando, lastComando;
    lastComando = r_stampa;
    numEntry = leggiFile(fileName, entries);
    if(numEntry == -1) return -1;
    while((comando = leggiComando()) != r_fine){
        doCmd(entries, numEntry, comando, lastComando);
        if(comando >= r_ordina_data && comando <= r_ordina_arrivo) lastComando = comando;
    }
    return 0;
}

int leggiFile(char *nomeFile, Entry entries[MAXENTRIES]){
    FILE* logFile = fopen(nomeFile, "r");
    if(logFile == NULL) return -1;
    int numEntry = 0, i;
    fscanf(logFile, "%d", &numEntry);
    for(i = 0; i < numEntry; i++){
        fscanf(logFile, "%s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d", entries[i].id, entries[i].partenza, entries[i].destinazione, &entries[i].data.aaaa, &entries[i].data.mm,
               &entries[i].data.gg, &entries[i].oraPartenza.hh, &entries[i].oraPartenza.mm, &entries[i].oraPartenza.ss, &entries[i].oraPartenza.hh,
               &entries[i].oraPartenza.mm, &entries[i].oraPartenza.ss, &entries[i].ritardo);
        entries[i].data.dataToInt = entries[i].data.gg + entries[i].data.mm*31 + entries[i].data.aaaa*365;
        entries[i].oraPartenza.oraToInt = entries[i].oraPartenza.hh*3600 + entries[i].oraPartenza.mm*60 + entries[i].oraPartenza.ss;
        entries[i].oraArrivo.oraToInt = entries[i].oraArrivo.hh*3600 + entries[i].oraArrivo.mm*60 + entries[i].oraArrivo.ss;
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

void doCmd(Entry *entries, int len, comando_e cmd, comando_e lastCmd){
    FILE* fp;
    char buff[MAX];
    int i;
    switch(cmd) {
        case r_stampa:
            printf("Dove vuoi stampare? (stdout o nomeFile): ");
            scanf("%s", buff);
            if (strcmp(buff, "stdout") == 0){
                for(i = 0; i < len; i++) stampaOccorrenza(entries[i], stdout);
            }else{
                fp = fopen(buff, "w");
                if(fp == NULL){
                    printf("Non posso aprire il file.");
                }else{
                    for(i = 0; i < len; i++) stampaOccorrenza(entries[i], fp);
                    fclose(fp);
                }
            }
            printf("\n");
            break;
        case r_ordina_data:
            ordinaData(entries, len);
            break;
        case r_ordina_tratta:
            ordinaTratta(entries, len);
            break;
        case r_ordina_partenza:
            ordinaPartenza(entries, len);
            break;
        case r_ordina_arrivo:
            ordinaArrivo(entries, len);
            break;
        case r_cerca:
            cerca(entries, len, lastCmd);
            break;
        default:
            printf("Comando errato, riprovare!\n");
    }
}

void ordinaData(Entry entries[MAXENTRIES], int len){
    int i, j;
    Entry tmp;
    for(i = 1; i < len; i++){
        tmp = entries[i];
        for(j = i-1; j >= 0 && tmp.data.dataToInt < entries[j].data.dataToInt; j--){
            entries[j+1] = entries[j];
        }
        entries[j+1] = tmp;
    }
}
void ordinaTratta(Entry entries[MAXENTRIES], int len){
    int i, j;
    Entry tmp;
    for(i = 1; i < len; i++){
        tmp = entries[i];
        for(j = i-1; j >= 0 && strcmp(tmp.id, entries[j].id) < 0; j--){
            entries[j+1] = entries[j];
        }
        entries[j+1] = tmp;
    }
}

void ordinaPartenza(Entry entries[MAXENTRIES], int len){
    int i, j;
    Entry tmp;
    for(i = 1; i < len; i++){
        tmp = entries[i];
        for(j = i-1; j >= 0 && strcmp(tmp.partenza, entries[j].partenza) < 0; j--){
            entries[j+1] = entries[j];
        }
        entries[j+1] = tmp;
    }
}
void ordinaArrivo(Entry entries[MAXENTRIES], int len){
    int i, j;
    Entry tmp;
    for(i = 1; i < len; i++){
        tmp = entries[i];
        for(j = i-1; j >= 0 && strcmp(tmp.destinazione, entries[j].destinazione) < 0; j--){
            entries[j+1] = entries[j];
        }
        entries[j+1] = tmp;
    }
}
void cerca(Entry entries[MAXENTRIES], int len, comando_e lastCmd){
    int i, m, l, r;
    char buff[MAX];
    printf("Inserisci stazione da cercare: ");
    scanf("%s", buff);
    if(lastCmd == r_ordina_partenza){
        l = 0;
        r = len-1;
        while(l <= r){
            m = (l+r)/2;
            if(strcmp(entries[m].partenza, buff) == 0){
                stampaOccorrenza(entries[m], stdout);
                break;
            }
            if(strcmp(entries[m].partenza, buff) < 0){
                l = m+1;
            }else{
                r = m-1;
            }
        }
    }else{
        for(i = 0; i < len; i++){
            if(strstr(entries[i].partenza, buff) != NULL) stampaOccorrenza(entries[i], stdout);
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