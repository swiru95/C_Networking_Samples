/*
 ============================================================================
 Name        : Z9_Swidrak.c
 Author      : Swidrak
 Version     :
 Copyright   : Private
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

struct A {
    __uint8_t a1 :1, a2 :1, a3 :1, a4 :1, a5 :1, a6 :1, a7 :1, a8 :1;
};
struct B {
    __uint8_t b1 :1, b2 :1, b3 :1;
};
struct C {
    __uint8_t c1 :1, c2 :1, c3 :4;
};

int main(void) {
    struct A a;
    struct B b;
    struct C c;
    puts("Zadanie Dziewiate"); /* prints Zadanie Dziewiate */
    printf("\n%i", sizeof(a));
    printf("\n%i", sizeof(b));
    printf("\n%i", sizeof(c));

    //Zamiast pisac a.a1=0 itd...
    char* x = &a;
    *x = 0x11;
    x = &b;
    *x = 0x0F;
    x = &c;
    *x = 0xF1;

    printf("\n\nA:%.2x", a);
    printf("\nPOSZCZEGOLNE\na1=%x a2=%x a3=%x a4=%x a5=%x a6=%x a7=%x a8=%x",
            a.a1, a.a2, a.a3, a.a4, a.a5, a.a6, a.a7, a.a8);
    printf("\nB:%.2x", b);
    printf("\nPOSZCZEGOLNE\nb1=%x b2=%x b3=%x ", b.b1, b.b2, b.b3);
    printf("\nC:%.2x", c);
    printf("\nPOSZCZEGOLNE\nc1=%x c2=%x c3=%.2x ", c.c1, c.c2, c.c3);
    return EXIT_SUCCESS;
}
