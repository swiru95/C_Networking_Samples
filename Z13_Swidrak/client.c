#include"head.h"
void* client_thread(void* V) {
    Client.msg = malloc(MSG_SIZE);
    Client.state = START; ///////////STATE
    Client.hostName = "localhost";
    Client.sockDesc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (Client.sockDesc < 0)
        getError("ERROR#9#client.c- Cant open socket!");
    char addr[15], port[9];
    //TODO WYBIERANIE SERVERA
    printf("\nCLIENT: Enter servers IPv4 address:");
    fgets(addr, 15, stdin);
    printf("\nCLIENT: Enter servers port (default 10000):");
    fgets(port, 9, stdin);
    /////////////////////////////////////////////////////////
    // strcpy(addr, "127.0.0.23");
    //strcpy(port, "10000");
    //////////////////////////////////////////////////////////
    Client.servPortNum = (int) strtol(port, (char **) NULL, 10);
    if (Client.servPortNum == 0)
        Client.servPortNum = SERVER_PORT_LISTEN;
    printf("\nCLIENT: You have chosen:\nCLIENT: IP: %s \nCLIENT: UDP Port: %d",
            addr, Client.servPortNum);
    bzero((char*) &(Client.serverAddr), sizeof(Client.serverAddr));
    Client.serverAddr.sin_family = AF_INET;
    Client.serverAddr.sin_addr.s_addr = inet_addr(addr);
    Client.serverAddr.sin_port = htons(Client.servPortNum);
    ////////////////////////////////////////////////////////////Initial MSG
    Client.msg->dataType = INI;
    Client.msg->opType = NOOP;
    bzero(Client.msg->data, DATA_SIZE);
    Client.serverAddrLen = sizeof(Client.serverAddr);
    Client.dataSize = sendto(Client.sockDesc, Client.msg, sizeof(*Client.msg),
            0, (struct sockaddr*) &(Client.serverAddr), Client.serverAddrLen);
    if (Client.dataSize < 0)
        getError("ERROR#32#client.c- Cant sent INI msg!");
    int res = pthread_create(&timer_thread, NULL, timer, NULL);
    if (res != 0)
        perror("#Cannot create Timer Thread!");
    ///////////////////////////////////////////////////////////////////////
    Client.status = NOCONNECTION;
    while (1) {
        pthread_mutex_trylock(&counter_lock);
        //CHECKING CONNECTION!!
        if (Client.status == NOCONNECTION) {
            Client.dataSize = recvfrom(Client.sockDesc, Client.msg,
            MSG_SIZE, 0, (struct sockaddr*) &(Client.serverAddr),
                    &(Client.serverAddrLen));
            if (Client.msg->dataType == ACK) {
                Client.status = CONNECTION;
                Client.state = STANDBY;
                printf("\n!!CLIENT: WE HAVE CONNECTION WITH SERVER"
                        "\n          Its ready to serve!");
            } else {
                perror("\n!!CLIENT: NO CONNECTION WITH SERVER!");
            }
        } else if (Client.status == CONNECTION) {
            //STANDBY
            if (Client.state == STANDBY) {
                setOp(Client.msg);
                if (strcmp(Client.op, "SUM") == 0) {
                    Client.msg->opType = SUM;
                } else if (strcmp(Client.op, "DIF") == 0) {
                    Client.msg->opType = DIF;
                } else if (strcmp(Client.op, "SUP") == 0) {
                    Client.msg->opType = SUP;
                } else if (strcmp(Client.op, "SDW") == 0) {
                    Client.msg->opType = SDW;
                }
                Client.msg->dataSize = strlen(Client.msg->data);
                Client.dataSize = sendto(Client.sockDesc, Client.msg,
                MSG_SIZE, 0, (struct sockaddr*) &(Client.serverAddr),
                        Client.serverAddrLen);
                if (Client.dataSize < 0)
                    getError("ERROR#31#client.c- Cant sent msg!");
                int res = pthread_create(&timer_thread, NULL, timer, NULL);
                if (res != 0)
                    perror("#Cannot create Timer Thread!");
                bzero(Client.op, OPERATION_SIZE);
                bzero(Client.msg, MSG_SIZE);
                Client.state = SENDING;
            }
            //SENDING
            else if (Client.state == SENDING) {
                Client.dataSize = recvfrom(Client.sockDesc, Client.msg,
                MSG_SIZE, 0, (struct sockaddr*) &(Client.serverAddr),
                        &(Client.serverAddrLen));
                if (Client.msg->dataType == RESP) {
                    Client.state = STANDBY;
                    if (Client.msg->opType == SUM
                            || Client.msg->opType == DIF) {
                        printf("\nCLIENT: Received from server: %d",
                                *Client.msg->data);
                    } else if (Client.msg->opType == SUP
                            || Client.msg->opType == SDW) {
                        printf("\nCLIENT: Received from server: %s",
                                Client.msg->data);
                    }
                }
            }
        }
        pthread_mutex_unlock(&counter_lock);
    }
    free(Client.msg);
    return NULL;
}
