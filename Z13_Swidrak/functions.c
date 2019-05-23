#include"head.h"

void getError(char* mer) {
    perror(mer);
    exit(1);
}
void* timer(void *x) {
    sleep(3);
    if (Client.status == NOCONNECTION) {
        puts("There is no connection with server!");
        pthread_cancel(client_t);
    } else {
        Client.state = STANDBY;
    }
    return NULL;
}
void sum(void* x) {
    char* data = (char*) x;
    int i = 0, eq = 0;
    while (i < strlen(data) - 1) {
        eq = eq + (*(data + i) - '0');
        i++;
    }
    printf("SERVER: COUNTED %d\n", eq);
    bzero(data, DATA_SIZE);
    *data = eq;
}
int checksum(void* x) {
    char* data = (char*) x;
    int i = 0, eq = 0;
    while (i < strlen(data) - 1) {
        eq = eq + (*(data + i) - '0');
        i++;
    }
    return eq;
}
void dif(void* x) {
    char* data = (char*) x;
    int i = 0, eq = 0;
    while (i < strlen(data) - 1) {
        eq = eq - (*(data + i) - '0');
        i++;
    }
    printf("SERVER: COUNTED %d\n", eq);
    bzero(data, DATA_SIZE);
    *data = eq;
}
void setUp(void *x) {
    int k = strlen((char*) x) - 1;
    int l = k;
    int tab[l + 1];
    while (l >= 0) {
        tab[l] = (int) (*(char*) (x + l) - '0');
        l--;
    }
    int n = (sizeof(tab) / sizeof(tab[0])) - 1;
    quickSort(tab, 0, n);
    l = k;
    while (l>=0) {
        *(char*) (x + l) = (char) (tab[l] + '0');
        l--;
    }
}
void setDown(void *x) {
    int k = strlen((char*) x) - 1, l = k;
    int tab[l];
    while (l >= 0) {
        tab[l] = (int) (*(char*) (x + l) - '0');
        l--;
    }
    l++;
    int n = (sizeof(tab) / sizeof(tab[0])) - 1;
    quickSort(tab, 0, n);
    while (l <= k) {
        *(char*) (x + l) = (char) (tab[k - l] + '0');
        l++;
    }
}
void setOp(struct message* msg) {
    bzero(Client.op, OPERATION_SIZE);
    bzero(msg->data, DATA_SIZE);
    printf("\nCLIENT: Enter a data: ");
    fgets(msg->data, DATA_SIZE, stdin);
    printf("\nCLIENT: Data: %s \nCLIENT: Enter a kind of operation: ",
            msg->data);
    fgets(Client.op, OPERATION_SIZE, stdin);
    printf("\nCLIENT: You have chosen %s!!", Client.op);
    msg->dataType = REQ;
}
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
void swap(int* a, int* b) {
    int toSwap = *a;
    *a = *b;
    *b = toSwap;
}
void addEl(struct buffor* B, void *x) {
    if (Server.counter == LIST_COUNT) {
        printList(B);
        Server.counter = 0;
        return;
    }
    char* D = (char*) ((struct message*) x)->data;
    if (B->prev == NULL && B->next == NULL && Server.isFirst) {
        B->checksum = checksum(D);
        Server.isFirst = 0;
        return;
    }
    struct buffor* new = malloc(sizeof(struct buffor));
    Server.counter++;
    new->ini = B;
    while (B->next != NULL) {
        B = B->next;
    }
    B->next = new;
    new->prev = B;
    new->checksum = checksum(D);
}
void clear(struct buffor* B) {
    struct buffor* del = B, *hp = B;
    while (hp != NULL) {
        hp = del->next;
        free(del);
        del = hp;
    }
}
void printList(struct buffor* B) {
    printf("\nSERVER: LIST:");
    while (B->next != NULL) {
        printf("\n    %d) checksum=%d ", LIST_COUNT - Server.counter,
                B->checksum);
        B = B->next;
        Server.counter--;
    }
    Server.counter=0;
    clear(B);
    printf("\nSERVER: LIST CLEARED!");
}
