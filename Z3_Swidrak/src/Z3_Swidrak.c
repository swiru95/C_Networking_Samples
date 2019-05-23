/*
 ============================================================================
 Name        : Z3_Swidrak.c
 Author      : Swidrak
 Version     :
 Copyright   : Private
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    puts("Zadanie Trzecie"); /* prints Zadanie Trzecie */
    int i = 0, j = 100;
    printf("\nOto zmienne: %i, %i", i, j);
    int spr = i + 20;
    for (i; i < spr; i++) {
        j -= 2;
    }
    printf("\nOto zmienne: %i, %i", i, j);
    int x = 20;
    while (x--) {
        i += 2;
        j += 2;
    }
    printf("\nOto zmienne: %i, %i", i, j);
    return EXIT_SUCCESS;
}
