#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<dlfcn.h>
#include<errno.h>
#include<unistd.h>
#include<math.h>

#define SERVER_PORT_LISTEN 10000
#define DATA_SIZE 22
#define MSG_SIZE 25
#define OPERATION_SIZE 4
#define LIST_COUNT 10

enum conStat {
    NOCONNECTION = 0, CONNECTION = 1
};
enum state {
    START = 1, STANDBY = 2, SENDING = 3, RECEIVING = 4
};
enum typeData {
    INI = 0x00, ACK = 0x01, REQ = 0x02, RESP = 0x11, ERR = 0xFF
};
enum typeOp {
    SUM = 0x0A, DIF = 0x0B, SUP = 0x0C, SDW = 0x0D, NOOP = 0xFF
};
struct client {
    int sockDesc, servPortNum, dataSize, state, status;
    socklen_t serverAddrLen;
    struct sockaddr_in serverAddr;
    struct hostent *server;
    struct message* msg;
    char *hostName, op[4];
} Client;
struct server {
    int sockDesc, myPortNum, dataSize, optval, state, counter, isFirst;
    socklen_t clientAddrLen;
    struct sockaddr_in serverAddr, clientAddr;
    struct hostent *hostCon;
    struct message* msg;
    char *hostIpAddr;
    struct buffor* Buff;
} Server;
struct message {
    char dataType, opType, dataSize, data[22];
};
struct buffor {
    struct buffor* ini, *next, *prev;
    int checksum;
};

pthread_mutex_t counter_lock;
pthread_t client_t, server_t, timer_thread, interrupt_t;

void* interruptThread(void*);
void* server_thread(void*);
void* client_thread(void*);
void* timer(void*);
void getError(char*);
void sum(void*);
void dif(void*);
void setUp(void*);
void setDown(void*);
void setOp(struct message *);
void swap(int* a, int* b);
void quickSort(int arr[], int low, int high);
int partition(int arr[], int low, int high);
void printList(struct buffor*);
void addEl(struct buffor*, void *);
void clear(struct buffor*);

