//
// Created by Ruggero Nocera on 11/01/2020.
//

#ifndef APA_LAB_DATE_H
#define APA_LAB_DATE_H

#include <stdio.h>
typedef struct{
    int hh;
    int mm;
} ORARIO;

typedef struct{
    int aaaa;
    int mm;
    int gg;
} DATA;


int DATAcmp(DATA d1, DATA d2); //-1 se d1 < d2, 0 se d1 == d2, 1 se d1 > d2
DATA DATAsetNull();
DATA DATAload(FILE *fp);
void DATAstore(DATA d, FILE *fp);
#endif //APA_LAB_DATE_H
