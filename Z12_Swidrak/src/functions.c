#include "head.h"
#include <dlfcn.h>

int checkKind(char * ch) {
    void* handle = dlopen(
            "/home/chris/omnetpp-5.2.1/samples/Z12_Swidrak/src/dynLib.so",
            RTLD_NOW);
    if (!handle) {
        printf("ERROR #8F: Bad opening %s", dlerror());
        return -10;
    }
    int (*fun)(char *) =(int (*)(char *)) dlsym(handle, "getProt"), i;
    if (fun == NULL) {
        printf("#14 DL getProt: %s", dlerror());
    }
    i = fun(ch);
    void (*fun1)(char *)=dlsym(handle, "printEthHdr");
    if (fun1 == NULL) {
        printf("#14 DL pEH: %s", dlerror());
    }
    if (i == 0x11) {
        puts("\n$$$$$$$$$$$$$$$$$-- UDP PACKET --$$$$$$$$$$$$$$$$$$\n");
        fun1(ch);
        fun1 = dlsym(handle, "printIpHdr");
        if (fun1 == NULL) {
            printf("#14 DL pIH: %s", dlerror());
        }
        fun1(ch);
        fun1 = dlsym(handle, "printUDP");
        if (fun1 == NULL) {
            printf("#14 DL pUD: %s", dlerror());
        }
        fun1(ch);
        i = 1;
    } /*else if (i == 0x01) {
     puts("\nICMP PACKET\n");
     fun1(ch);
     fun1 = dlsym(handle, "printIpHdr");
     if (fun1 == NULL) {
     printf("#14 DL pIH: %s", dlerror());
     }
     fun1(ch);
     fun1 = dlsym(handle, "printIcmp");
     if (fun1 == NULL) {
     printf("#14 DL pIH: %s", dlerror());
     }
     fun1(ch);
     i = 2;
     } */else {
        //puts("\nThere is not UDP!");
        i = 0;
    }
    if (dlclose(handle)) {
        perror("Error #44 with closing library!");
    }
    return i;
}
void *sniffThread(void* argb) {

    char* B = malloc(ETH_FRAME_LEN);
    int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sock < 0) {
        perror("ERROR #17 Socket failure.");
    }
    setsockopt(sock, SOL_SOCKET, SO_BINDTODEVICE, "", 1);
    //ini el
    struct element* buffor = malloc(sizeof(struct element));
    while (1) {
        int i = 20;
        int len = recv(sock, B, ETH_FRAME_LEN, 0);
        buffor->len = len;
        buffor->i = 0;
        buffor->prev = NULL;
        buffor->next = NULL;
        buffor->ini = buffor;
        buffor->frame = malloc(len);
        memcpy(buffor->frame, B, len);
        while (i) {
            int len = recv(sock, B, ETH_FRAME_LEN, 0);
            if (len == -1) {
                perror("ERROR #60F Frame failure.");
            } else if (htons(*(B + 12)) == 0x800
                    && htons(*(B + 23)) == 0x1100) {
                addEl(buffor, len, B);
                i--;
            }
        }
        struct element* actual = buffor;
        while (actual->next != NULL) {
            if (checkKind(actual->frame) == 1) {
                printf(
                        "\n\n Odebrano ramke Ethernet,Ipv4,UDP o dlugosci %d\nTo jest %d w BUFFOR,\nRAMKA:",
                        actual->len, actual->i);
            }
            actual = actual->next;
        }
        actual = buffor;
        while (actual->next != NULL) {
            printf("\nCzyszcze %d w BUFFOR\n", actual->i);
            free(actual->frame);
            actual = actual->next;
        }
    }
    free(B);
    puts("\nCapturing finished.");
    return NULL;
}
void *cThread(void * X) {

    char x;
    while (1) {
        scanf("%c", &x);
        if (x == 'E') {
            pthread_cancel(s_thread);
            puts("\n Capturing has been cancelled by user!");
            return NULL;
        }
    }

}
void addEl(struct element* f, int size, char* B) {
    struct element* new = malloc(sizeof(struct element));
    if (new == NULL) {
        perror("ERROR new==NULL ln 23");
    }
    while (f->next != NULL) {
        f = f->next;
    }
    new->frame = malloc(size);
    memcpy(new->frame, B, size);
    new->len = size;
    f->next = new;
    new->ini = f->ini;
    new->prev = f;
    new->next = NULL;
    new->i = new->prev->i + 1;

}

