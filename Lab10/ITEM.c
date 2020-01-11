//
// Created by Ruggero Nocera on 10/01/2020.
//

#include "ITEM.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define MAXC 20
struct item{
    char *label;
    char *net;
};

ITEM ITEMnew(char* label, char* net){
    ITEM ret = malloc(sizeof(*ret));
    ret->label = calloc(MAXC, sizeof(char));
    ret->net = calloc(MAXC, sizeof(char));
    strncpy(ret->label, label, MAXC);
    strncpy(ret->net, net, MAXC);
    return ret;
}

void ITEMfree(ITEM item){
    if(item == NULL) return;
    free(item->label);
    free(item->net);
    free(item);
}

char *ITEMgetLabel(ITEM item){
    char *ret = calloc(MAXC, sizeof(char));
    strncpy(ret, item->label, MAXC);
    return ret;
}

char *ITEMgetNet(ITEM item){
    char *ret = calloc(MAXC, sizeof(char));
    strncpy(ret, item->net, MAXC);
    return ret;
}

void ITEMdisplay(ITEM item){
    printf("%s %s\n", item->label, item->net);
}