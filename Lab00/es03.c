//
// Created by Ruggero Nocera on 03/10/2019.
//

#include "stdio.h"
#define maxN 30

void ruota(int v[maxN], int n, int p, int dir);
int main(){
    int i, N, input, p;
    int vett[maxN];
    setbuf(stdout, NULL);
    printf("Inserisci N: ");
    scanf("%d", &N);

    printf("Scrivi %d numeri separati da spazio: ", N);
    for(i = 0; i < N; i++) scanf("%d", &vett[i]);


    do{
        printf("Direzione: ");
        scanf("%d", &input);
        printf("Posizioni: ");
        scanf("%d", &p);
        if(p <= 0) return -1;
        ruota(vett, N, p, input);
        for(i = 0; i < N; i++) printf("%d ", vett[i]);
        printf("\n");
    }while(p > 0);
    return 0;
}

/*void ruota(int v[maxN], int n, int p, int dir){
    int i = 0, j = 0;
    int tmp_prev = 0, tmp_next = 0;
    if(dir == -1){
        for(j = 0; j < p; j++){
            tmp_prev = v[0];
            for(i = 0; i < n; i++){
                tmp_next = v[(i+1)%n];
                v[(i+1)%n]= tmp_prev;
                tmp_prev = tmp_next;
            }
        }
    }else if(dir == 1){
        for(j = 0; j < p; j++){
            tmp_prev = v[0];
            for(i = n-1; i > 0; i--){
                tmp_next = v[i];
                v[i] = tmp_prev;
                tmp_prev = tmp_next;
            }
            v[0] = tmp_prev;
        }
    }
}*/

void ruota(int v[maxN], int n, int p, int dir){
    int tmp, i, j, cnt;
    if(dir == -1) p = n-p; //P spostamenti a DX = N-P spostamenti a SX

    for(cnt = 0, i = 0; cnt < n; i++, cnt++){
        tmp = v[i];
        for(j = i; ((j+p)%n) != i; j = (j+p)%n, cnt++){
            v[j] = v[(j+p)%n];
        }
        v[j] = tmp;
    }
}
