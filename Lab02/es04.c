//
// Created by Ruggero Nocera on 20/10/2019.
// Selection Sort, Insertion Sort, Shell Sort
//

#include <stdio.h>
#define MAX 30
#define fileName "sort.txt"

void selectionSort(int *vett, int n);
void insertionSort(int *vett, int n);
void shellSort(int *vett, int n);

int main(){
    FILE *fileSort;
    int numSeq, i, j, dim;
    int vett[MAX];

    fileSort = fopen(fileName, "r");
    if (fileSort == NULL) return -1;
    setbuf(stdout, NULL);
    fscanf(fileSort, "%d", &numSeq);
    for(i = 0; i < numSeq; i++){
        fscanf(fileSort, "%d", &dim);
        for(j = 0; j < dim; j++){
            fscanf(fileSort, "%d", &vett[j]);
        }
        printf("Selection sort:\n");
        selectionSort(vett, dim);
        printf("Insertion sort:\n");
        insertionSort(vett, dim);
        printf("Shell sort:\n");
        shellSort(vett, dim);
    }

    fclose(fileSort);
    return 0;
}

void insertionSort(int *vett, int n){
    int tmp[n];
    int iterazioni[n-1];
    int i, j, x;
    int numScambi, numTotale, it;
    numScambi = numTotale = 0;

    for(i = 0; i < n; i++) tmp[i] = vett[i];
    for(i = 0; i < n-1; i++) iterazioni[i] = 0;

    for(i = 1; i < n; i++){
        numTotale++;
        x = tmp[i];
        j = i-1;
        it = 0;
        while(j >= 0 && x < tmp[j]){
            tmp[j+1] = tmp[j];
            numTotale++;
            numScambi++;
            it++;
            j--;
        }
        iterazioni[i-1] = it;
        tmp[j+1] = x;
    }
    printf("Per ordinare il vettore ho eseguito: %d scambi, %d iterazioni del ciclo esterno, e per ogni iterazione:\n", numScambi, i-1);
    for(i = 0; i < n-1; i++){
        printf("%d iterazione: %d iterazioni ciclo interno\n", i+1, iterazioni[i]);
    }
    printf("Per un totale di %d iterazioni\nVettore ordinato: ", numTotale);
    for(i = 0; i < n; i++) printf("%d ", tmp[i]);
    printf("\n");
}

void selectionSort(int *vett, int n){
    int i, j, min;
    int tmp;
    int tmpVett[n];
    int iterazioni[n-1];
    for(i = 0; i < n; i++) tmpVett[i] = vett[i];
    int numScambi, numTotale, it;
    numScambi = numTotale = 0;

    for(i = 0; i < n-1; i++){
        numTotale++;
        it = 0;
        min = i;
        for(j = i+1; j < n; j++){
            it++;
            numTotale++;
            if(tmpVett[j] < tmpVett[min])
                min = j;
        }
        if(min != i){
            numScambi++;
            tmp = tmpVett[i];
            tmpVett[i] = tmpVett[min];
            tmpVett[min] = tmp;
        }
        iterazioni[i] = it;
    }
    printf("Per ordinare il vettore ho eseguito: %d scambi, %d iterazioni del ciclo esterno, e per ogni iterazione:\n", numScambi, i-1);
    for(i = 0; i < n-1; i++){
        printf("%d iterazione: %d iterazioni ciclo interno\n", i+1, iterazioni[i]);
    }
    printf("Per un totale di %d iterazioni\nVettore ordinato: ", numTotale);
    for(i = 0; i < n; i++) printf("%d ", tmpVett[i]);
    printf("\n");
}

void shellSort(int *vett, int n){
    int i, j, h = 1, tmpVett[n];

    int tmp;
    for(i = 0; i < n; i++) tmpVett[i] = vett[i];
    while(h < n/3)
        h = 3*h+1;
    while(h>=1){
        for(i = h; i <= n-1; i++){
            j = i;
            tmp = tmpVett[i];
            while(j >= h && tmp < tmpVett[j-h]){

                tmpVett[j] = tmpVett[j-h];
                j-=h;
            }
            tmpVett[j] = tmp;
        }
        h = h/3;
    }
    printf("Vettore ordinato: ");
    for(i = 0; i < n; i++) printf("%d ", tmpVett[i]);
    printf("\n");
}