#include <stdio.h>
#include <ctype.h>
int conta(char S[20], int n);
int isVocal(char c);
int main() {
    FILE *fp;
    char nomeFile[21];
    char string[20];
    int N = 0, i, tot = 0;
    int len;
    printf("Nome file: ");
    scanf("%s", nomeFile);
    printf("Lunghezza sottostringhe: ");
    scanf("%d", &len);

    fp = fopen(nomeFile, "r");
    if(fp == NULL) return -1;
    fscanf(fp, "%d", &N);

    for(i = 0; i < N; i++){
        fscanf(fp, "%s", string);
        tot += conta(string, len);
    }

    printf("%d sottostringhe trovate", tot);
    return 0;
}

int conta(char S[20], int n){
    int i = 0, j = 0;
    int numVocali = 0;
    int totSubString = 0;
    for(i = 0; S[i] != '\0' && i + n < 20; i++){
        numVocali = 0;
        for(j = 0; j < n; j++){
            if(isVocal(S[i+j])) numVocali++;
        }
        if(numVocali == 2) totSubString++;
    }
    return totSubString;
}

int isVocal(char c){
    c = (char) tolower(c);
    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') return 1;
    return 0;
}