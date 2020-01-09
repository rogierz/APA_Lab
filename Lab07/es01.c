//
// Created by Ruggero Nocera on 22/11/2019.
//

#include <stdio.h>
#include <stdlib.h>
typedef enum{
    p_zaffiri, p_rubini, p_topazi, p_smeraldi, p_pietre
} e_pietre;

char* nomi[p_pietre] = {"Z", "R", "T", "S"};

void generaCollane(int *val, int len);
int generaCollaneR(int pos, int *val, int len, int *sol, int k);

int main(int argc, char *argv[]){
    int pietre[p_pietre];
    int i;
    setbuf(stdout, NULL);
    FILE *fp = fopen(argv[1], "r");
    int nTest;
    fscanf(fp, "%d", &nTest);
    for (i = 0; i < nTest; i++) {
        fscanf(fp, "%d %d %d %d", &pietre[0], &pietre[1], &pietre[2], &pietre[3]);
        printf("TEST #%d\n", i+1);
        printf("z = %d, r = %d, t = %d, s = %d\n", pietre[0], pietre[1], pietre[2], pietre[3]);
        generaCollane(pietre, p_pietre);
    }
    fclose(fp);
    return 0;
}

void generaCollane(int *val, int len){
    int i = 0, j = 0;
    int *sol;
    int tmp = 0;
    for(i = 0; i < len; i++){
        tmp += val[i];
    }
    sol = malloc(tmp* sizeof(int));

    for(i = tmp; i > 0; i--){
        if(generaCollaneR(0, val, len, sol, i)){
            for(j = 0; j < i; j++)
                printf("%s", nomi[sol[j]]);
            break;
        }
    }
    printf("TOT: %d\nLUNGHEZZA TROVATA: %d\n", tmp,  j);
    free(sol);
}

int generaCollaneR(int pos, int *val, int len, int *sol, int k){
    int i, flag = 0;

    if(pos>=k){
        return 1;
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
        }
        if(val[i] > 0){
            val[i]--;
            sol[pos] = i;
            if(generaCollaneR(pos+1, val, len, sol, k)) flag = 1;
            val[i]++;
            if(flag) return 1;
        }
    }

    return 0;
}