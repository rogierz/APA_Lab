#include <stdio.h>
#define N 10
int main() {
    int vett[N];
    int i, j;
    int dim_max = 0;
    int dim_att = 0;
    setbuf(stdout, NULL);
    printf("Scrivi 10 numeri separati da spazio: ");
    for(i = 0; i < N; i++) {
        scanf("%d", &vett[i]);
    }
    for(i = 0; i < N; i++){
        if(vett[i] != 0){
            for( ; vett[i] != 0 && i < N; i++) dim_att++;
            if(dim_att > dim_max) dim_max = dim_att;
            dim_att = 0;
        }
    }

    for(i = 0; i < N; i++){
        for(j = i; vett[j] != 0 && j < N; j++);
        if(j-i == dim_max){
            printf("{");
            for(; vett[i] != 0 && i < N; i++) printf("%d", vett[i]);
            printf("} ");
        }
    }
    return 0;
}