/*
 * head.h
 *
 *  Created on: Apr 17, 2018
 *      Author: chris
 */
/*Its a network sniffer for ICMP and UDP which are delivered by IPv4
 *It operates with two threads. One is sniffing and the second is waiting
 *for interruption (scanf) from user. The key which couses to terminate the program
 *is "E". Preffered to enter shift+e.
 */
#ifndef HEAD_H_
#define HEAD_H_
//Includes
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <linux/if_ether.h>
#include <pthread.h>
#include <unistd.h>
#include <error.h>

struct element {
    struct element* next;
    struct element* prev;
    struct element* ini;

    int i,len;

    char* frame;
};


pthread_t s_thread, c_thread;

void addEl(struct element*,int,char*);
int checkKind(char*);
void *sniffThread(void*);
void *cThread(void*);
#endif /* HEAD_H_ */
