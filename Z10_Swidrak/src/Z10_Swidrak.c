/*
 ============================================================================
 Name        : Z10_Swidrak.c
 Author      : Swidrak
 Version     :
 Copyright   : Private
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct S {
    unsigned char a, b, c, d;
};

int main(void) {
    puts("Zadanie Dziesiate"); /* prints Zadanie Dziesiate */
    int a = 0x11223344;
    struct S* s = malloc(sizeof(struct S));
    memcpy(s, &a, 4);
    printf(
            "\n STRUCT:\n  a= %x  0x%x  b= %x  0x%x  c= %x  0x%x  d= %x  0x%x\n CALOSCIOWO:%i w hexa: 0x%x",
            s->a, s->a, s->b, s->b, s->c, s->c, s->d, s->d, *s, *s);

    if (__BYTE_ORDER == __BIG_ENDIAN) {
        puts("\n  BigEndian!");
    } else if (__BYTE_ORDER == __LITTLE_ENDIAN) {
        puts("\n  LittleEndian!");
    } else {
        perror("Error with ORDER #33");
    }

    return EXIT_SUCCESS;
}
