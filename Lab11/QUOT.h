//
// Created by Ruggero Nocera on 11/01/2020.
//

#ifndef APA_LAB_QUOT_H
#define APA_LAB_QUOT_H

#include "DATE.h"
typedef struct bstquot * BSTQUOT;
typedef struct quot QUOT;

struct quot{
    DATA data;
    float val;
    int den;
};

void QUOTstore(QUOT q, FILE *fp);
float QUOTgetVal(QUOT q);
BSTQUOT BSTQUOTinit();
void BSTQUOTfree(BSTQUOT bst);
void BSTQUOTinsert(BSTQUOT bst, DATA d, float val, int num);
QUOT BSTQUOTsearch(BSTQUOT bst, DATA d);
void BSTQUOTstore(BSTQUOT bst, FILE *fp);
void BSTQUOTminmax(BSTQUOT bst, float *min, float *max);
void BSTQUOTminMaxRange(BSTQUOT bst, DATA d1, DATA d2, float *f1, float *f2);
int BSTQUOTmaxHeight(BSTQUOT bst);
int BSTQUOTminHeight(BSTQUOT bst);
void BSTQUOTbalance(BSTQUOT bst);
#endif //APA_LAB_QUOT_H
