//
// Created by Ruggero Nocera on 17/10/2019.
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
    r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine, r_err
} comando_e;
void strToLower(char *str);
comando_e leggiComando();
void selezionaDati(Entry *entries, int len, comando_e cmd);
void date(Entry *entries, int len);
void partenza(Entry *entries, int len);
void capolinea(Entry *entries, int len);
void ritardo(Entry *entries, int len);
void ritardo_tot(Entry *entries, int len);
int main(){
    FILE* logFile = fopen(fileName, "r");
    if(logFile == NULL) return -1;
    setbuf(stdout, NULL);
    Entry entries[MAXENTRIES];
    int numEntry = 0, i;
    comando_e comando;
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
    while((comando = leggiComando()) != r_fine){
            selezionaDati(entries, numEntry, comando);
    }
}

comando_e leggiComando(){
    comando_e c;
    char *cmdTable[r_err] = {"date", "partenza", "capolinea", "ritardo", "ritardo_tot", "fine"};
    char cmd[MAX];
    printf("Comando (date/partenza/capolinea/ritardo/ritardo_tot/fine: ");
    scanf("%s", cmd);
    strToLower(cmd);
    c = r_date;
    while(c < r_err && strcmp(cmd, cmdTable[c]) != 0){
        c++;
    }
    return c;
}

void selezionaDati(Entry *entries, int len, comando_e cmd){
    switch(cmd){
        case r_date:
            date(entries, len);
            break;
        case r_partenza:
            partenza(entries, len);
            break;
        case r_capolinea:
            capolinea(entries,len);
            break;
        case r_ritardo:
            ritardo(entries, len);
            break;
        case r_ritardo_tot:
            ritardo_tot(entries, len);
            break;
        default:
            printf("Comando errato, riprovare!\n");
    }
}
void stampaOccorrenza(Entry entry){
    printf("%s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d\n", entry.id, entry.partenza, entry.destinazione,
           entry.data.gg, entry.data.mm, entry.data.aaaa,
           entry.oraPartenza.hh, entry.oraPartenza.mm, entry.oraPartenza.ss,
           entry.oraArrivo.hh, entry.oraArrivo.mm, entry.oraArrivo.ss, entry.ritardo);
}
void date(Entry *entries, int len){
    int i;
    struct data dataInizio, dataFine;
    printf("Inserisci intervallo date (gg/mm/aaaa): ");
    scanf("%d/%d/%d %d/%d/%d", &dataInizio.gg, &dataInizio.mm, &dataInizio.aaaa, &dataFine.gg, &dataFine.mm, &dataFine.aaaa);
    dataInizio.dataToInt = dataInizio.gg + dataInizio.mm*31 + dataInizio.aaaa*365;
    dataFine.dataToInt = dataFine.gg + dataFine.mm*31 + dataFine.aaaa*365;
    for(i = 0; i < len; i++){
        if(dataInizio.dataToInt <= entries[i].data.dataToInt && entries[i].data.dataToInt <= dataFine.dataToInt){
            stampaOccorrenza(entries[i]);
        }
    }
}
void partenza(Entry *entries, int len){
    int i;
    char fermata[MAX];
    printf("Inserisci nome fermata: ");
    scanf("%s", fermata);
    for(i = 0; i < len; i++){
        if(strcmp(fermata, entries[i].partenza) == 0)
            stampaOccorrenza(entries[i]);
    }
}
void capolinea(Entry *entries, int len){
    int i;
    char fermata[MAX];
    printf("Inserisci nome fermata: ");
    scanf("%s", fermata);
    for(i = 0; i < len; i++){
        if(strcmp(fermata, entries[i].destinazione) == 0)
            stampaOccorrenza(entries[i]);
    }
}
void ritardo(Entry *entries, int len){
    int i;
    struct data dataInizio, dataFine;
    printf("Inserisci intervallo date (gg/mm/aaaa): ");
    scanf("%d/%d/%d %d/%d/%d", &dataInizio.gg, &dataInizio.mm, &dataInizio.aaaa, &dataFine.gg, &dataFine.mm, &dataFine.aaaa);
    dataInizio.dataToInt = dataInizio.gg + dataInizio.mm*31 + dataInizio.aaaa*365;
    dataFine.dataToInt = dataFine.gg + dataFine.mm*31 + dataFine.aaaa*365;
    for(i = 0; i < len; i++){
        if(dataInizio.dataToInt <= entries[i].data.dataToInt && entries[i].data.dataToInt <= dataFine.dataToInt && entries[i].ritardo > 0){
            stampaOccorrenza(entries[i]);
        }
    }
}
void ritardo_tot(Entry *entries, int len){
    int i, ritardo = 0;
    char id[MAX];
    printf("Inserisci codice tratta: ");
    scanf("%s", id);
    for(i = 0; i < len; i++){
        if(strcmp(id, entries[i].id) == 0) ritardo += entries[i].ritardo;
    }
    printf("Ritardo complessivo per le tratte %s: %d\n", id, ritardo);
}

void strToLower(char *str){
    int i;
    for(i = 0; str[i] != '\0'; i++) str[i] = tolower(str[i]);
}