//
// Created by Ruggero Nocera on 11/01/2020.
//

#include "QUOT.h"
#include <stdlib.h>

typedef struct bstnode *link;
struct bstnode{
    QUOT q;
    link l, r;
    int cnt;
};
struct bstquot{
    link root;
    link z;
    int cnt;
};

static link NEWnode(DATA data, float val, int den, link l, link r){
    link x = malloc(sizeof(struct bstnode));
    x->l = l;
    x->r = r;
    x->q.data = data;
    x->q.val = val * den;
    x->q.den = den;
    x->cnt = 1;
    return x;
}
BSTQUOT BSTQUOTinit(){
    BSTQUOT bst = malloc(sizeof(struct bstquot));
    bst->z = NEWnode(DATAsetNull(), -1.0, 0, NULL, NULL);
    bst->z->cnt = 0;
    bst->root = bst->z;
    bst->cnt = 0;
    return bst;
}

static void freeR(link h, link z){
    if(h == z)
        return;
    freeR(h->l, z);
    freeR(h->r, z);
    free(h);
}
void BSTQUOTfree(BSTQUOT bst){
    freeR(bst->root, bst->z);
}
static link insertR(link h, link z, DATA d, float val, int num, int *add){
    int cmp;
    if(h == z){
        *add = 1;
        return NEWnode(d, val, num, z, z);
    }
    cmp = DATAcmp(d, h->q.data);
    if(cmp == 1){
        h->l = insertR(h->l, z, d, val, num, add);
    } else if (cmp == -1){
        h->r = insertR(h->r, z, d, val, num, add);
    }else{
        h->q.val = h->q.val + val*num;
        h->q.den += num;
    }
    if(*add) h->cnt++;
    return h;
}
void BSTQUOTinsert(BSTQUOT bst, DATA d, float val, int num){
    int add = 0;
    bst->root = insertR(bst->root, bst->z, d, val, num, &add);
    if(add) bst->cnt++;
}

static QUOT searchR(link h, link z, DATA d){
    int cmp = DATAcmp(d, h->q.data);
    if(cmp == 0){
        return h->q;
    } else if (cmp == 1){
        return searchR(h->r, z, d);
    }else{
        return searchR(h->l, z, d);
    }
}
QUOT BSTQUOTsearch(BSTQUOT bst, DATA d){
    return searchR(bst->root, bst->z, d);
}

static void storeR(link h, link z, FILE *fp){
    if(h == z)
        return;
    storeR(h->l, z, fp);
    QUOTstore(h->q, fp);
    storeR(h->r, z, fp);
}
void BSTQUOTstore(BSTQUOT bst, FILE *fp){
    storeR(bst->root, bst->z, fp);
    printf("\n");
}
static float media(QUOT q){
    if(q.den != 0)
        return q.val/q.den;
    return -1.0;
}

void QUOTstore(QUOT q, FILE *fp){
    DATAstore(q.data, fp);
    fprintf(fp, "%.2f %d\n", q.val, q.den);
}
static void minmax(link h, link z, float *min, float *max){
    if(h == z)
        return;
    float q = QUOTgetVal(h->q);
    if(q > *max || *max <= 0)
        *max = q;
    if(q < *min || *min <= 0)
        *min = q;
    minmax(h->l, z, min, max);
    minmax(h->r, z, min, max);
}

void BSTQUOTminmax(BSTQUOT bst, float *min, float *max){
    if(bst == NULL) return;
    minmax(bst->root, bst->z,  min, max);
}

void treeMinMaxRange(link h, link z, DATA d1, DATA d2, float *f1, float *f2){
    int cmp1, cmp2;
    cmp1 = DATAcmp(d1, h->q.data); //1 se d1 > q.data
    cmp2 = DATAcmp(d2, h->q.data); //1 se d2 > q.data
    if(h == z)
        return;
    if(cmp1 == -1){
        treeMinMaxRange(h->l, z, d1, d2, f1, f2);
    }
    if(cmp2 == 1){
        treeMinMaxRange(h->r, z, d1, d2, f1, f2);
    }
    if(cmp1 <= 0 && cmp2 >= 0){
        if(QUOTgetVal(h->q) < *f1 || *f1 <= 0)
            *f1 = QUOTgetVal(h->q);
        if(QUOTgetVal(h->q) > *f2 || *f2 <= 0)
            *f2 = QUOTgetVal(h->q);
    }
}
void BSTQUOTminMaxRange(BSTQUOT bst, DATA d1, DATA d2, float *f1, float *f2){
    if(bst == NULL) return;
    return treeMinMaxRange(bst->root, bst->z, d1, d2, f1, f2);
}
static int maxHeightR(link h, link z){
    if(h == z)
        return 0;
    int maxL = maxHeightR(h->l, z);
    int maxR = maxHeightR(h->r, z);
    return ((maxL <= maxR) ? maxR : maxL) + 1;
}
int BSTQUOTmaxHeight(BSTQUOT bst){
    return maxHeightR(bst->root, bst->z);
}
static int minHeightR(link h, link z){
    if(h == z)
        return 0;
    int minL = minHeightR(h->l, z);
    int minR = minHeightR(h->r, z);
    return ((minL >= minR) ? minR : minL) + 1;
}
int BSTQUOTminHeight(BSTQUOT bst){
    return minHeightR(bst->root, bst->z);
}
static link rotR(link h){
    link x = h->l;
    h->l = x->r;
    x->r = h;
    x->cnt = h->cnt;
    h->cnt = 1;
    h->cnt += h->l->cnt;
    h->cnt += h->r->cnt;
    return x;
}

static link rotL(link h){
    link x = h->r;
    h->r = x->l;
    x->l = h;
    x->cnt = h->cnt;
    h->cnt = 1;
    h->cnt += h->l->cnt;
    h->cnt += h->r->cnt;
    return x;
}

static link partR(link h, link z, int r){
    if(h == z)
        return z;
    int t = h->l->cnt;
    if(t > r){
        h->l = partR(h->l, z, r);
        h = rotR(h);
    }
    if(t < r){
        h->r = partR(h->r, z, r-t-1);
        h = rotL(h);
    }
    return h;
}


void BSTQUOTbalance(BSTQUOT bst){
   int r = (bst->cnt+1)/2-1;
   bst->root = partR(bst->root, bst->z, r);
}

float QUOTgetVal(QUOT q){
    return media(q);
}


