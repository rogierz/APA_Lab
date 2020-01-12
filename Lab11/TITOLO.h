//
// Created by Ruggero Nocera on 11/01/2020.
//

#ifndef APA_LAB_TITOLO_H
#define APA_LAB_TITOLO_H

#include "DATE.h"
#include "QUOT.h"
typedef struct titolo_s * TITOLO;
typedef struct listTitoli_s * LISTtitoli;


TITOLO TITOLOnew(char *nome);
void TITOLOfree(TITOLO t);
char * TITOLOgetKey(TITOLO t);
void TITOLOaddTransazione(TITOLO t, DATA d, float val, int qta);
void TITOLOstore(TITOLO t, FILE *fp);
QUOT TITOLOsearchQuot(TITOLO t, DATA d);
void TITOLOminMaxRange(TITOLO t, DATA d1, DATA d2, float *min, float *max);
void TITOLOminmax(TITOLO t, float *min, float *max);
float TITOLObstRatio(TITOLO t);
void TITOLObalanceBst(TITOLO t);
LISTtitoli LISTinit();
void LISTaddTitolo(LISTtitoli l, TITOLO t);
TITOLO LISTsearchTitolo(LISTtitoli l, char *cod);
void LISTstore(LISTtitoli l, FILE *fp);
void LISTfree(LISTtitoli l);
#endif //APA_LAB_TITOLO_H
