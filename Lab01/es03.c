//
// Created by Ruggero Nocera on 11/10/2019.
//

#include <stdio.h>
#include <string.h>
#define MAXLEN 20
#define MAXMATR 30
#define MAXBUF 100

void ruota(int matr[MAXMATR][MAXMATR], int nr, int nc, int index, int sel, int dir, int pos);

int main(){
    FILE* fileMatrice;
    setbuf(stdout, NULL);
    char fileName[MAXLEN];
    char sel[MAXBUF];
    char dir[MAXBUF];
    char buffer[MAXBUF];
    int index, pos;
    int matrice[MAXMATR][MAXMATR];
    int nr, nc;
    int i, j;
    printf("Inserisci nome file: ");
    scanf("%s", fileName);
    fileMatrice = fopen(fileName, "r");
    if(fileMatrice == NULL) return -1;
    fscanf(fileMatrice, "%d %d", &nr, &nc);
    for(i = 0; i < nr; i++){
        for(j = 0; j < nc; j++){
            fscanf(fileMatrice, "%d", &matrice[i][j]);
        }
    }
    printf("<selettore> <indice> <direzione> <posizioni>:\n");
    fflush(stdin);
    while(gets(buffer) != NULL){
        if(sscanf(buffer, "%s %d %s %d", sel, &index, dir, &pos) != 4 && strcmp(sel, "fine") == 0) break;
        if(strcmp(sel, "riga") == 0){
            if(index > nc){
                printf("Input non corretto. (Index error)\n");
                continue;
            }
            if(strcmp(dir, "destra") == 0){
                ruota(matrice, nr, nc, index-1, 0, -1, pos);
            }else if(strcmp(dir, "sinistra") == 0){
                ruota(matrice, nr, nc, index-1, 0, 1, pos);
            }else{
                printf("Input non corretto.\n");
            }
        }else if(strcmp(sel, "colonna") == 0){
            if(index > nr){
                printf("Input non corretto. (Index error)\n");
                continue;
            }
            if(strcmp(dir, "su") == 0){
                ruota(matrice, nr, nc, index-1, 1, 1, pos);
            }else if(strcmp(dir, "giu") == 0){
                ruota(matrice, nr, nc, index-1, 1, -1, pos);
            }else{
                printf("Input non corretto.\n");
            }
        }
        printf("<selettore> <indice> <direzione> <posizioni>:\n");
    }

    for(i = 0; i < nr; i++){
        for(j = 0; j < nc; j++) printf("%d ", matrice[i][j]);
        printf("\n");
    }
    return 0;
}

void ruota(int matr[MAXMATR][MAXMATR], int nr, int nc, int index, int sel, int dir, int pos){
    int tmp, i, j, cnt;
    switch(sel){
        case 0:
            if(dir == -1) pos = nc-pos;
            for(cnt = 0, i = 0; cnt < nc; i++, cnt++){
                tmp = matr[index][i];
                for(j = i; (j+pos)%nc != i; j = (j+pos)%nc, cnt++) matr[index][j] = matr[index][(j+pos)%nc];
                matr[index][j] = tmp;
            }
            break;
        case 1:
            if(dir == -1) pos = nr-pos;
            for(cnt = 0, i = 0; cnt < nr; i++, cnt++){
                tmp = matr[i][index];
                for(j = i; (j+pos)%nr != i; j = (j+pos)%nr, cnt++) matr[j][index] = matr[(j+pos)%nr][index];
                matr[j][index] = tmp;
            }
            break;
    }
}