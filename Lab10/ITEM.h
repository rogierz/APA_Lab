//
// Created by Ruggero Nocera on 10/01/2020.
//

#ifndef APA_LAB_ITEM_H
#define APA_LAB_ITEM_H

typedef struct item *ITEM;
ITEM ITEMnew(char *label, char *net);
void ITEMfree(ITEM item);
char *ITEMgetLabel(ITEM item);
char *ITEMgetNet(ITEM item);
void ITEMdisplay(ITEM item);
#endif //APA_LAB_ITEM_H
