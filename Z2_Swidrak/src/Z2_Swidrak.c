/*
 ============================================================================
 Name        : Z2_Swidrak.c
 Author      : Swidrak
 Version     :
 Copyright   : Private
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    puts("Zadanie Drugie"); /* prints Zadanie Drugie */

    int zi = 1;
    char zch = 'c';
    unsigned char zuch = 'x';
    float zfl = 6.91324;
    double zdb = 1.01;

    const int zci = 10;

    printf(
            "\n Int: %i \nChar: %c \nUchar: %c \nFloat: %f \nDouble: %f\nConstINt: %i",
            zi, zch, zuch, zfl, zdb, zci);
    //zci=100; !!!??JAK??!!!
    int *a = &zci;
    *a = 30;

    printf(
            "\n Int: %i \nChar: %c \nUchar: %c \nFloat: %f \nDouble: %f\nConstINt: %i",
            zi, zch, zuch, zfl, zdb, zci);
    printf(
            "\nRozmiary: \n Int: %d \nChar: %d \nUchar: %d \nFloat: %d \nDouble: %d\nConstINt: %d",
            sizeof(zi), sizeof(zch), sizeof(zuch), sizeof(zfl), sizeof(zdb),
            sizeof(zci));
    return EXIT_SUCCESS;
}
