//
// Created by Ruggero Nocera on 30/11/2019.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct tile_t{
    char oColore;
    char vColore;
    int oPeso;
    int vPeso;
    int fissa;
    int usata;
} tile;

typedef struct board_t{
    int i;
    int ruota;
} boardCell;

tile ruotaTile(tile t);
void generaSoluzione(boardCell **board, int nr, int nc, tile **tiles, int nTiles);
void generaSoluzioneR(int pos, boardCell **board, int nr, int nc, tile **tiles, int nTiles, boardCell **bestBoard, int *bestPunteggio);
int calcolaPunteggio(boardCell **board, int nr, int nc, tile *tiles, int nTiles);

int main(){
    setbuf(stdout, NULL);
    tile* tiles;
    boardCell** board;
    int i, j, nTiles, tmp;
    int nr, nc;
    FILE* fileTiles = fopen("tiles.txt", "r");
    FILE* fileBoard = fopen("board.txt", "r");

    if(fileTiles == NULL || fileBoard == NULL) return -1;
    fscanf(fileTiles, "%d%*c", &nTiles);
    tiles = calloc(nTiles, sizeof(struct tile_t));
    for(i = 0; i < nTiles; i++){
        fscanf(fileTiles, "%c %d %c %d%*c", &tiles[i].oColore, &tiles[i].oPeso, &tiles[i].vColore, &tiles[i].vPeso);
        tiles[i].fissa = 0;
        tiles[i].usata = 0;
    }
    fscanf(fileBoard, "%d %d", &nr, &nc);
    board = calloc(nr, sizeof(struct board_t *));
    for(i = 0; i < nr; i++){
        board[i] = calloc(nc, sizeof(struct board_t));
        for(j = 0; j < nc; j++){
            fscanf(fileBoard, "%d/%d", &board[i][j].i, &board[i][j].ruota);
            if(board[i][j].i != -1){
                tiles[board[i][j].i].fissa = 1;
                tiles[board[i][j].i].usata = 1;
            }
        }
    }

    fclose(fileTiles);

    printf("Tessere lette:\n");
    for(i = 0; i < nTiles; i++){
        printf("%c %d %c %d\n", tiles[i].oColore, tiles[i].oPeso, tiles[i].vColore, tiles[i].vPeso);
    }
    printf("Board letta:\n");
    for(i = 0; i < nr; i++){
        for(j = 0; j < nc; j++){
            tmp = -1;
            if(board[i][j].i != -1) tmp = board[i][j].ruota;
            printf("%d/%d ", board[i][j], tmp);
            }
        printf("\n");
    }

    generaSoluzione(board, nr, nc, &tiles, nTiles);
    return 0;
}

void generaSoluzione(boardCell **board, int nr, int nc, tile **tiles, int nTiles){
    boardCell **bestBoard = calloc(nr, sizeof(boardCell *));
    int bestPunteggio = 0;
    int i, j;
    for(i = 0; i < nr; i++){
        bestBoard[i] = calloc(nc, sizeof(boardCell));
    }
    generaSoluzioneR(0, board, nr, nc, tiles, nTiles, bestBoard, &bestPunteggio);
    printf("Soluzione ottima:\n");
    for(i = 0; i < nr; i++){
        for(j = 0; j < nc; j++){
            printf("%d/%d ", bestBoard[i][j].i, bestBoard[i][j].ruota);
        }
        printf("\n");
    }
    printf("Punteggio massimo: %d\n", bestPunteggio);
}

void generaSoluzioneR(int pos, boardCell **board, int nr, int nc, tile **tiles, int nTiles, boardCell **bestBoard, int *bestPunteggio){
    int i, j, k, currPunteggio;
    i = pos/nr;
    j = pos%nc;
    if(pos >= nr*nc){
        currPunteggio = calcolaPunteggio(board, nr, nc, *tiles, nTiles);
        if(currPunteggio > *bestPunteggio){
            *bestPunteggio = currPunteggio;
            for(i = 0; i < nr; i++){
                for(j = 0; j < nc; j++){
                    bestBoard[i][j] = board[i][j];
                }
            }
        }
        return;
    }

    if(board[i][j].i >= 0){
        return generaSoluzioneR(pos+1, board, nr, nc, tiles, nTiles, bestBoard, bestPunteggio);
    }
    for(k = 0; k < nTiles; k++) {
        if ((*tiles)[k].usata == 0) {
            (*tiles)[k].usata = 1;
            board[i][j].i = k;
            board[i][j].ruota = 0;
            generaSoluzioneR(pos + 1, board, nr, nc, tiles, nTiles, bestBoard, bestPunteggio);
            board[i][j].ruota = 1;
            generaSoluzioneR(pos + 1, board, nr, nc, tiles, nTiles, bestBoard, bestPunteggio);
            (*tiles)[k].usata = 0;
            board[i][j].i = -1;
        }
    }
}

int calcolaPunteggio(boardCell **board, int nr, int nc, tile *tiles, int nTiles){
    int punteggioOrizzontale = 0;
    int punteggioVerticale = 0;
    int i, j;
    int tmp = 0;
    tile tilesTmp[nTiles];
    for(i = 0; i < nTiles; i++){
        tilesTmp[i] = tiles[i];
    }
    for(i = 0; i < nr; i++){
        for(j = 0; j < nc; j++){
            if(board[i][j].ruota == 1){
                tilesTmp[board[i][j].i] = ruotaTile(tilesTmp[board[i][j].i]);
            }
        }
    }
    for(i = 0; i < nr; i++){
        tmp = 0;
        for(j = 0; j < nc; j++){
            if(tilesTmp[board[i][j].i].oColore == tilesTmp[board[i][0].i].oColore)  tmp++;
        }
        if(tmp == nc){
            for(j = 0; j < nc; j++){
                punteggioOrizzontale += tilesTmp[board[i][j].i].oPeso;
            }
        }
    }
    for(j = 0; j < nc; j++){
        tmp = 0;
        for(i = 0; i < nr; i++){
            if(tilesTmp[board[i][j].i].vColore == tilesTmp[board[0][j].i].vColore) tmp++;
        }
        if(tmp == nr){
            for(i = 0; i < nr; i++){
                punteggioVerticale += tilesTmp[board[i][j].i].vPeso;
            }
        }
    }
    return punteggioOrizzontale+punteggioVerticale;
}
tile ruotaTile(tile t){
    tile tmp;
    tmp.vColore = t.oColore;
    tmp.vPeso = t.oPeso;
    tmp.oColore = t.vColore;
    tmp.oPeso = t.vPeso;
    return tmp;
}