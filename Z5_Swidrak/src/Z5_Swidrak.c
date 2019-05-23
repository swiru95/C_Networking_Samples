/*
 ============================================================================
 Name        : Z5_Swidrak.c
 Author      : Swidrak
 Version     :
 Copyright   : Private
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
int glob = 1;

int suma(int a, int b) {
    printf("\nWynik suma1: %i", a + b);
    return a + b;
}
int suma2(int a, int b) {
    int loc = 3;
    loc += a + b;
    printf("\nWynik suma2: %i", loc);
    return loc;
}
int suma3(int a,int *b) {
    int loc=10,x;
    x= a + *b;
    *b=loc+x;
    return x;
}

int main(void) {

    puts("Zadanie Piate"); /* prints Zadanie Piate */
    int loc = 2,*wloc=&loc;
    int x = suma(loc, glob);
    x = suma2(loc, glob);
    x = suma3(glob,wloc);
    printf("\nWynik suma3: %i, Wskaznik: *wloc=%i",x,*wloc);

    return EXIT_SUCCESS;
}
