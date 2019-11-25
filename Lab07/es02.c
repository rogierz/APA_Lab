//
// Created by Ruggero Nocera on 22/11/2019.
//

#include <stdio.h>
#include <stdlib.h>
#define MAX_RIP 4

typedef enum{
    p_zaffiri, p_smeraldi, p_rubini, p_topazi, p_pietre
} e_pietre;

char* nomi[p_pietre] = {"Zaffiro", "Smeraldo", "Rubino", "Topazio"};
int valori[p_pietre];

void generaCollane(int *val, int len);
void generaCollaneR(int pos, int *val, int len, int *sol, int k, int *bestSol, int *bestSolLen, int *bestSolVal);
int calcolaValoreVerifica(int *sol, int len);

int main(){
    int pietre[p_pietre];
    int i;
    setbuf(stdout, NULL);
    for(i = 0; i < p_pietre; i++){
        printf("Inserisci quantita di [%s]: ", nomi[i]);
        scanf("%d", &pietre[i]);
        fflush(stdout);
        valori[p_pietre-i-1] = (i+1)*2;
    }
    generaCollane(pietre, p_pietre);
    return 0;
}

void generaCollane(int *val, int len){
    int i = 0;
    int *sol;
    int *bestSol;
    int bestSolLen = 0;
    int bestSolVal = 0;
    int tmp = 0;
    for(i = 0; i < len; i++){
        tmp += val[i];
    }
    sol = malloc(tmp* sizeof(int));
    bestSol = malloc(tmp* sizeof(int));
    for(i = tmp; i > 0; i--){
        generaCollaneR(0, val, len, sol, i, bestSol, &bestSolLen, &bestSolVal);
    }
    for(i = 0; i < bestSolLen; i++){
        printf("%s %d\n", nomi[bestSol[i]], valori[bestSol[i]]);
    }
    printf("TOT: %d\nLUNGHEZZA TROVATA: %d\nVALORE: %d", tmp,  bestSolLen, bestSolVal);
    free(sol);
    free(bestSol);
}

void generaCollaneR(int pos, int *val, int len, int *sol, int k, int *bestSol, int *bestSolLen, int *bestSolVal){
    int i, j, count, tmp;

    if(pos>=k){
        if((tmp = calcolaValoreVerifica(sol, k)) != -1){
            if(tmp > *bestSolVal && k > *bestSolLen){
                *bestSolVal = tmp;
                *bestSolLen = k;
                for(i = 0; i < k; i++){
                    bestSol[i] = sol[i];
                }
            }
        }
        return;
    }

    for(i = 0; i < len; i++){
        if(pos > 0){
            if(sol[pos - 1] == p_zaffiri ||  sol[pos - 1] == p_topazi){
                if(i != p_zaffiri && i != p_rubini){
                    continue;
                }
            }
            if(sol[pos - 1] == p_smeraldi || sol[pos - 1] == p_rubini){
                if(i != p_smeraldi && i != p_topazi){
                    continue;
                }
            }
            for(j = pos-1, count = 1; j >= 0 && sol[j] == i && count < MAX_RIP+1; j--, count++);
            if(count > MAX_RIP) continue;
        }
        if(val[i] > 0){
            val[i]--;
            sol[pos] = i;
            generaCollaneR(pos+1, val, len, sol, k, bestSol, bestSolLen, bestSolVal);
            val[i]++;
        }
    }
}

int calcolaValoreVerifica(int *sol, int len){
    int occ[p_pietre];
    int tot = 0;
    int i;
    for(i = 0; i < p_pietre; i++) occ[i] = 0;
    for(i = 0; i < len; i++){
        occ[sol[i]]++;
    }
    for(i = 0; i < p_pietre; i++) tot += occ[i]*valori[i];
    if(occ[p_zaffiri] > occ[p_smeraldi]) tot = -1;
    return tot;
}