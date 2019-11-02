//
// Created by Ruggero Nocera on 02/11/2019.
//

#include <stdio.h>

int gcd(int a, int b);
int main(){
    int a, b;
    printf("Inserisci due numeri: ");
    scanf("%d %d", &a, &b);
    printf("Il gcd e\' %d", gcd(a, b));
    return 0;
}

int gcd(int a, int b){
    if(b > a) return gcd(b, a);
    if (b == 0) return a;
    if(a % 2 == 0 && b % 2 == 0)
        return 2*gcd(a/2, b/2);
    if(a % 2 != 0 && b % 2 == 0)
        return gcd(a, b/2);
    if(a % 2 == 0 && b % 2 != 0)
        return gcd(a/2, b);
    if(a % 2 != 0 && b % 2 != 0)
        return gcd((a-b)/2, b);
}