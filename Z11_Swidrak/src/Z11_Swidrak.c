/*
 ============================================================================
 Name        : Z11_Swidrak.c
 Author      : Swidrak
 Version     :
 Copyright   : Private
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
struct element {
    struct element* next;
    struct element* prev;
    struct element* ini;

    __uint32_t seq;
};
void addEl(struct element* f) {
    struct element* new = malloc(sizeof(struct element));
    if (new == NULL) {
        perror("ERROR new==NULL ln 23");
    }
    while (f->next != NULL) {
        f = f->next;
    }
    f->next = new;
    new->ini = f->ini;
    new->prev = f;
    new->next = NULL;
    new->seq = f->seq + 1;
}
void delEl(struct element* f, int n) {
    struct element* del =f;
    while(1){
        del=del->next;
        if(del->seq==n){
            break;
        }
    }
    del->prev->next = del->next;
    del->next->prev = del->prev;
    free(del);
    del = NULL;
}
void printList(struct element* list) {
    while (list->next != NULL) {
        printf("\nLIST:0x%x \nIni: 0x%x ; Next: 0x%x ; Prev: 0x%x ; Seq: %i",
                list, list->ini, list->next, list->prev, list->seq);
        list = list->next;
    }
}
int main(void) {
    puts("Zadanie jedenaste"); /* prints Zadanie Dziesiate */
    //FIRST
    struct element* list = malloc(sizeof(struct element));
    if (list == NULL) {
        perror("ERROR ln 27. NULL on list!");
    }
    list->ini = list;
    list->next = NULL;
    list->prev = NULL;
    list->seq = 1;

    int i = 10;
    while (i) {
        addEl(list);
        i--;
    }
    printList(list);

    list=list->ini;
    puts("\nAfter del 5 and 7");
    delEl(list, 5);
    delEl(list, 7);
    printList(list);
    return EXIT_SUCCESS;
}
