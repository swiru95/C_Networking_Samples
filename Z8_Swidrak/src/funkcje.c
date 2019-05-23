/*
 ============================================================================
 Name        : Z8_Swidrak.c
 Author      : Swidrak
 Version     :
 Copyright   : Private
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include "funkcje.h"

int suma(int a, int b) {
    printf("\nWynik suma: %i", a + b);
    return a + b;
}
int suma2(int a, int b) {
    int loc = 3;
    loc += a + b;
    printf("\nWynik suma: %i", loc);
    return loc;
}
int suma3(struct struktura a) {
    int loc = 3,x;
    x=a.a + a.b;
    a.b=x+loc;
    printf("\nWynik suma loc: %i, %i,", x, a.b);
    return x;
}
