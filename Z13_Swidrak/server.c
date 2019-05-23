#include"head.h"
void* server_thread(void* V) {
    Server.state = START;
    Server.counter = 0;
    Server.isFirst = 1;
    Server.msg = malloc(MSG_SIZE);
    Server.Buff = malloc(sizeof(struct buffor));
    Server.Buff->ini = Server.Buff;
    Server.Buff->next = NULL;
    Server.Buff->prev = NULL;
    Server.Buff->checksum = -1;
    Server.myPortNum = SERVER_PORT_LISTEN;
    Server.sockDesc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (Server.sockDesc < 0) {
        getError("ERROR#8#server.c- Cant open socket!");
    }
    Server.optval = 1;
    setsockopt(Server.sockDesc, SOL_SOCKET, SO_REUSEADDR,
            (const void *) &(Server.optval), sizeof(int));
    bzero((char*) &(Server.serverAddr), sizeof(Server.serverAddr));
    Server.serverAddr.sin_family = AF_INET;
    Server.serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    Server.serverAddr.sin_port = htons(Server.myPortNum);
    if (bind(Server.sockDesc, (struct sockaddr*) &(Server.serverAddr),
            sizeof(Server.serverAddr)) < 0)
        getError("ERROR#21#server.c- Cant bind!");
    else {
        printf("\n!!!SUCCESS!!!\nSERVER UDP: started!");
        Server.state = STANDBY;
    }
    Server.clientAddrLen = sizeof(Server.clientAddr);
    while (1) {
        pthread_mutex_trylock(&counter_lock);
        if (Server.state == STANDBY) {
            Server.dataSize = recvfrom(Server.sockDesc, Server.msg, MSG_SIZE, 0,
                    (struct sockaddr *) &(Server.clientAddr),
                    &(Server.clientAddrLen));
            if (Server.dataSize < 0)
                getError("ERROR#33#server.c- Error in recv!");
            Server.state = RECEIVING;
        }
        if (Server.state == RECEIVING) {
            if (Server.msg->dataType == INI)
            //INI
                    {
                printf("\nSERVER: INI");
                Server.msg->dataType = ACK;
                puts("\nSERVER: Connected to the HOST!");
                pthread_cancel(timer_thread);
                if (Server.dataSize < 0)
                    getError("ERROR#55#server.c- Error in sendto!");
                Server.state = STANDBY;
            }
            //REQUEST
            else if (Server.msg->dataType == REQ) {
                if (strlen(Server.msg->data)) {
                    addEl(Server.Buff, Server.msg);
                }
                Server.msg->dataType = RESP;
                //SUM
                if (Server.msg->opType == SUM) {
                    puts("\nSERVER: OP SUM");
                    sum(Server.msg->data);
                }
                //DIF
                else if (Server.msg->opType == DIF) {
                    puts("\nSERVER: OP DIF");
                    dif(Server.msg->data);
                } else if (Server.msg->opType == SUP) {
                    puts("\nSERVER: OP SUP");
                    setUp(Server.msg->data);
                } else if (Server.msg->opType == SDW) {
                    puts("\nSERVER: OP SDW");
                    setDown(Server.msg->data);
                }
                //OTHER NOT ACCEPTED
                else {
                    Server.msg->dataType = ERR;
                    Server.msg->opType = NOOP;
                    strcpy(Server.msg->data, "OP NOT ACCEPTED");
                }
                Server.state = STANDBY;
            }
            Server.dataSize = sendto(Server.sockDesc, Server.msg,
                    sizeof(*Server.msg), 0,
                    (struct sockaddr *) &(Server.clientAddr),
                    Server.clientAddrLen);
        }
        pthread_mutex_unlock(&counter_lock);
    }
    free(Server.Buff);
    free(Server.msg);
    return NULL;
}
