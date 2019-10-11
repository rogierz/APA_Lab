//
// Created by Ruggero Nocera on 06/10/2019.
//

#include <stdio.h>
#include <string.h>
#define MAX 200
#define S 30
#define src "sorgente.txt"
#define dict "dizionario.txt"
#define dest "ricodificato.txt"

int main(){
    FILE *fileSrc, *fileDict, *fileDest;
    fileSrc = fopen(src, "r");
    fileDict = fopen(dict, "r");
    fileDest = fopen(dest, "w");
    char subRiga[MAX];
    char newSubRiga[MAX];
    char c;
    int dictDim, found, good;
    char dictionary[S][MAX];
    char substitution[S][MAX];
    int i, j, k, s, t = 0, lenFound;
    if(fileSrc == NULL || fileDict == NULL || fileDest == NULL) return -1;
    fscanf(fileDict, "%d", &dictDim);
    for(i = 0; i < dictDim; i++){
        fscanf(fileDict, "%s %s", substitution[i], dictionary[i]);
    }
    fclose(fileDict);
    while(fgets(subRiga, MAX, fileSrc) != NULL){ //leggo riga per riga il file
        i = 0;
        while(subRiga[i] != '\0'){ //leggo carattere per carattere la riga letta
            found = -1;
            lenFound = 0;
            for(j = 0; j < dictDim; j++){
                k = 0;
                good = 1;
                while(dictionary[j][k] != '\0' && good){
                    if(dictionary[j][k] != subRiga[i+k]) good = 0;
                    k++;
                }
                if(good == 1){
                    found = j;
                    lenFound = k;
                }
            }
            if(found == -1) {
                newSubRiga[t++] = subRiga[i++];
            }else {
                s = 0;
                while (substitution[found][s] != '\0') {
                    newSubRiga[t++] = substitution[found][s++];
                }
                i += lenFound;
            }
        }
        newSubRiga[t] = '\0';
        fputs(newSubRiga, fileDest);
        t = 0;
        newSubRiga[t] = '\0';
    }
    fclose(fileSrc);
    fclose(fileDest);
    return 0;
}