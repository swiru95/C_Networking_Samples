/*
 ============================================================================
 Name        : Z6_Swidrak.c
 Author      : Swidrak
 Version     :
 Copyright   : Private
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    puts("Zadanie Szoste"); /* prints Zadanie Szoste */
    unsigned int* wsk_do_buffora, liczba_elementow_buffora = 8;
    wsk_do_buffora = malloc(liczba_elementow_buffora * sizeof(unsigned int));
    int i = liczba_elementow_buffora;
    while (i--) {
        *wsk_do_buffora = 100 + (8 - i);
        printf("\n %i", *wsk_do_buffora);
        wsk_do_buffora++;
    }
    printf("\nRozmar wsk: %d\n Liczba el buf: %d", sizeof(wsk_do_buffora),
            liczba_elementow_buffora);
    wsk_do_buffora -= liczba_elementow_buffora;
    free(wsk_do_buffora);
    puts("\nNOWE:");
    while (i++ < 7) {
        printf("\n %i", *wsk_do_buffora);
        wsk_do_buffora++;
    }
    puts("\n\nEND");
    return EXIT_SUCCESS;
}
