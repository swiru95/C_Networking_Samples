#include "funkcje.h"

int main(void) {
    puts("Zadanie Osme"); /* prints Zadanie Osme */
    struct struktura a;
    a.a=10;
    a.b=10;

    int x=suma(a.a, a.b);
    x=suma2(a.a, a.b);
    x=suma3(a);

    return EXIT_SUCCESS;
}
