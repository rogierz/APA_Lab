//
// Created by Ruggero Nocera on 25/10/2019.
//

#include <stdio.h>
#include <math.h>
int checkBigEndian();
void stampaCodifica(void *punt, int size, int bigEndian);

int main(){
    float af;
    double ad;
    long double ald;
    int bigEndian;
    bigEndian = checkBigEndian();

    printf("Inserisic un float, un double e un longd double: ");
    scanf("%f %lf %Lf", &af, &ad, &ald);

    stampaCodifica((void *)&af, sizeof(af), bigEndian);
    stampaCodifica((void *)&ad, sizeof(ad), bigEndian);
    stampaCodifica((void *)&ald, sizeof(ald), bigEndian);

}

void stampaCodifica(void *punt, int size, int bigEndian){
    unsigned char *p = (unsigned char *)punt;
    int start, end, step;
    int i, nBit = 0, exp = 0;
    int d, tmp;
    if(size == 16) size = 10;
    printf("Stampo %d bit (", size*8);
    switch(size){
        case 4:
            exp = 10;
            printf("float):\n");
            break;
        case 8:
            exp =  13;
            printf("double):\n");
            break;
        case 10:
            exp = 16;
            printf("long double), dovrebbero essere 128 ma a Windows non piace:\n");
            break;
    }

    printf("| SEGNO | ESPONENETE | MANTISSA |\n");
    if(bigEndian){
        start = 0;
        end = size;
        step = 1;
    }else{
        start = size-1;
        end = -1;
        step = -1;
    }
    printf("| ");
    for(i = start; i != end; i+=step){
        tmp = *(p+i);
        d = pow(2, 7);
        while(d > 0){
            nBit++;
            if(nBit == 2 || nBit == exp) printf(" | ");
            if(tmp >= d){
                printf("1");
                tmp -= d;
            }else{
                printf("0");
            }
            d/=2;
        }
    }
    printf(" |\n");
}
int checkBigEndian(){ //0 -> Little Endian | 1 -> Big Endian
    int val = 1;
    if(*(unsigned char *)&val == 1)
        return 0;
    return 1;
}

