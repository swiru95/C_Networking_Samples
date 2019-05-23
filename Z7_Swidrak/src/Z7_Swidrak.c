/*
 ============================================================================
 Name        : Z7_Swidrak.c
 Author      : Swidrak
 Version     :
 Copyright   : Private
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
struct struktura {
    unsigned char* wchar;
    int wint;
};
int main(void) {
    puts("Zadanie Siodme"); /* prints Zadanie Siodme */

    struct struktura zmienna_strukt;
    zmienna_strukt.wint = 123;
    zmienna_strukt.wchar = NULL;
    printf("\n Zmienna INT: %i,\n Zmienna *CHAR: 0x%x", zmienna_strukt.wint,
            zmienna_strukt.wchar);
    struct struktura* wsk_zmienna_strukt = &zmienna_strukt;
    wsk_zmienna_strukt->wchar = malloc(sizeof(char));
    *wsk_zmienna_strukt->wchar = 'A'; //Zmiana wartosci!! nie adresu!!??
    wsk_zmienna_strukt->wint = 100;
    printf("\n\n Zmienna INT: %i\n Zmienna *CHAR: %c", zmienna_strukt.wint,
            *zmienna_strukt.wchar);
    return EXIT_SUCCESS;
}
