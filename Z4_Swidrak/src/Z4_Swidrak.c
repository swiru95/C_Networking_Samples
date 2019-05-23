/*
 ============================================================================
 Name        : Z4_Swidrak.c
 Author      : Swidrak
 Version     :
 Copyright   : Private
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    puts("Zadanie Czwarte"); /* prints Zadanie Czwarte */

    int zint = 123, *wzi = &zint;
    char zchar = 'O', *wzch = &zchar;
    unsigned char zuchar = 'A', *wzuch = &zuchar;
    puts("\n\nRozmiary:");
    printf("\nINT: %d,  *: %d \nCHAR: %d,  *: %d \nUCHAR: %d,  *: %d ",
            sizeof(zint), sizeof(wzi), sizeof(zchar), sizeof(wzch),
            sizeof(zuchar), sizeof(wzuch));
    puts("\n\nWar:");
    printf("\nINT: %d,  *: %d \nCHAR: %d,  *: %d \nUCHAR: %d,  *: %d ", zint,
            *wzi, zchar, *wzch, zuchar, *wzuch);
    *wzi = 321;
    *wzch = 'U';
    *wzuch = 'B';
    puts("\n\nPo zmianie przez wsk:");
    puts("\n\nRozmiary:");
    printf("\nINT: %d,  *: %d \nCHAR: %d,  *: %d \nUCHAR: %d,  *: %d ",
            sizeof(zint), sizeof(wzi), sizeof(zchar), sizeof(wzch),
            sizeof(zuchar), sizeof(wzuch));
    puts("\n\nWar:");
    printf("\nINT: %d,  *: %d \nCHAR: %d,  *: %d \nUCHAR: %d,  *: %d ", zint,
            *wzi, zchar, *wzch, zuchar, *wzuch);

    return EXIT_SUCCESS;
}
