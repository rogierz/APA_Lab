//
// Created by Ruggero Nocera on 11/01/2020.
//

#include "DATE.h"
#include <stdio.h>

int DATAcmp(DATA d1, DATA d2){
    int d1Int;
    int d2Int;
    if(d1.gg == -1 && d2.gg != -1) return -1;
    if(d1.gg != -1 && d2.gg == -1) return 1;
    if(d1.gg == -1 && d2.gg == -1) return 0;
    d1Int = d1.aaaa*365+d1.mm*12+d1.gg;
    d2Int = d2.aaaa*365+d2.mm*12+d2.gg;
    int ret = 1;
    if(d2Int >= d1Int) ret = d2Int > d1Int ? -1 : 0;
    return ret;
}

DATA DATAsetNull(){
    DATA d;
    d.gg = -1;
    return d;
}

DATA DATAload(FILE *fp){
    DATA ret;
    fscanf(fp, "%d/%d/%d %*d:%*d", &ret.aaaa, &ret.mm, &ret.gg);
    return ret;
}

void DATAstore(DATA d, FILE *fp){
    fprintf(fp, "%02d/%02d/%04d ", d.gg, d.mm, d.aaaa);
}