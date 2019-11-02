//
// Created by Ruggero Nocera on 02/11/2019.
//

#include <stdio.h>
#define LEN 10
int majority(int *a, int N);
int majorityR(int *a, int l, int r);

int main(){
    int vett[LEN];
    int i;
    printf("Inserisci un vettore lungo %d: ", LEN);
    for(i = 0; i < LEN; i++) scanf("%d", &vett[i]);
    printf("Elemento maggioritario (-1 se non esiste): %d", majority(vett, 8));
    return 0;
}
int majority(int *a, int N){
    return majorityR(a, 0, N-1);
}
int majorityR(int *a, int l, int r){
    int m = (r+l)/2;
    int sx, dx, i;
    int occSx, occDx;
    occSx = occDx = 0;
    if(l == r) return a[l];
    if(r-l == 1){
        if(a[l] == a[r]) return a[l];
        return -1;
    }
    sx = majorityR(a, l, m);
    dx = majorityR(a, m+1, r);
    if(sx == -1 && dx == -1) return -1;
    for(i = l; i <= r; i++){
        if(a[i] == sx) occSx++;
        if(a[i] == dx) occDx++;
    }
    if(occSx >= occDx && occSx > (r-l+1)/2) return sx;
    if(occDx > (r-l+1)/2) return dx;
    return -1;

}