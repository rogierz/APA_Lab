//
// Created by Ruggero Nocera on 12/12/2019.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) a >= b ? a : b
#define N 7
void solve(int *val, int n);
int solveR(int *val, int *opt, int n, int k);
void solveDP(int *val, int n);
void displaySol(int *opt, int *val, int n);

int main(){
    int val[N+1] = {0, 14, 22, 13, 25, 30, 11, 90};
    solve(val, N);
    printf("\n");
    solveDP(val, N);
    return 0;
}

int solveR(int *val, int *opt, int n, int k){
    if(k == 0)
        return 0;
    if(k == 1)
        return val[1];
    return MAX(solveR(val, opt, n, k-1), solveR(val, opt, n, k-2) + val[k]);
}

void solve(int *val, int n){
    int *opt = calloc(n+1, sizeof(int));
    printf("Recursive solution:\n");
    printf("max pop covered: %d\n", solveR(val, opt, n, n));
}

void solveDP(int *val, int n){
    int i, *opt;
    opt = calloc((n+1), sizeof(int));
    opt[1] = val[1];
    for(i = 2; i <=  n; i++){
        if(opt[i-1] > opt[i-2] + val[i])
            opt[i] = opt[i-1];
        else
            opt[i] = opt[i-2] + val[i];
    }
    printf("Dynamic programming solution:\n");
    printf("max pop covered: %d\n", opt[n]);
    displaySol(opt, val, n);
}

void displaySol(int *opt, int *val, int n){
    int i, *sol;
    sol = calloc(n+1, sizeof(int));
    sol[1] = 1;
    i = n;
    while(i >= 2){
        printf("i = %d\n", i);
        if(opt[i] == opt[i-1]){
            sol[i] = 0;
            i--;
        }else if(opt[i] == opt[i-2] + val[i]){
            sol[i] = 1;
            sol[i-1] = 0;
            i -= 2;
        }
    }

    for(i = 1; i <= n; i++){
        if(sol[i])
            printf("%d ", val[i]);
    }
    printf("\n");
}