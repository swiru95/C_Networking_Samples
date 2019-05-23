#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <linux/if_ether.h> //ether header
#include <netinet/in.h>
#include <arpa/inet.h>

struct ipa {
    __u8 first, second, third, fourth;
};
struct frame {
//Eth from Linux
    struct ethhdr eHdr;
//IPv4
    __u8 ihl :4;
    __u8 version :4;
    __u8 tos;
    __be16 tot_len;
    __be16 id;
    __be16 frag_off;
    __u8 ttl;
    __u8 protocol;
    __sum16 check;
    struct ipa saddr;
    struct ipa daddr;

    unsigned char data[1480];
};
struct udph {
    __be16 sPort, dPort, len, check;
    unsigned char data[1472];
};
struct icmph {
    __u8 type, code;
    __be16 checksum;
    __be32 msi;
    unsigned char data[1472];
};
int getProt(char*);
void printEthHdr(char *);
void printIpHdr(char*);
void printUDP(char*);

int getProt(char * ch) {
    struct frame* buffer = (struct frame*) ch;
    int ax = sizeof(struct frame) - sizeof(struct ethhdr) - 1480;
    printf(
            "\n\n\n::ROZMIARY::STRUKTURY::RAMKOWEJ::\n\nROZMIAR Frame= %d\nETHHead= %d\nROZMIAR IPh=%d\nROZMIAR UDPh=%d\n",
            sizeof(struct frame), sizeof(struct ethhdr), ax,
            sizeof(struct udph)-1472);
    if (buffer->protocol == 0x11) {
        return 0x11; //UDP
    } else if (buffer->protocol == 0x01) {
        return 0x01; //ICMP
    } else {
        return 0;    //OTHER
    }
}
void printEthHdr(char * ch) {
    struct frame* buffer = (struct frame*) ch;
    int i = 0;
    printf("EHT:::::::::::\nDEST MAC ADDRESS:  0x ");
    while (i < 6) {
        printf("%.2x", buffer->eHdr.h_dest[i++]);
        if (i % 2 == 0 && i > 0 && i < 6) {
            printf("-");
        }
    }
    i = 0;
    printf("\nSOURCE MAC ADDRESS:  0x ");
    while (i < 6) {
        printf("%.2x", buffer->eHdr.h_source[i++]);
        if (i % 2 == 0 && i > 0 && i < 6) {
            printf("-");
        }
    }
    printf("\nPROTO TYPE: 0x %.4x\n", htons(buffer->eHdr.h_proto));
}
void printIpHdr(char * ch) {
    struct frame* buffer = (struct frame*) ch;
    printf(
            "\nIP:::::::::::::::::\nIPv: 0x%x\nHLen: 0x%x\nTOS: 0x%.2x\nTotLen: 0x%.4x\nID: 0x%.4x\nFRAGOff: 0x%.4x\nTTL: 0x%.2x\nPROTO: 0x%.2x\nCHECK: 0x%.4x\nSrADDR: 0x%.2x%.2x%.2x%.2x(%i.%i.%i.%i)\nDeADDR: 0x%.2x%.2x%.2x%.2x(%i.%i.%i.%i)\n",
            buffer->version, buffer->ihl, buffer->tos, htons(buffer->tot_len),
            htons(buffer->id), htons(buffer->frag_off), buffer->ttl,
            buffer->protocol, htons(buffer->check), buffer->saddr.first,
            buffer->saddr.second, buffer->saddr.third, buffer->saddr.fourth,
            buffer->saddr.first, buffer->saddr.second, buffer->saddr.third,
            buffer->saddr.fourth, buffer->daddr.first, buffer->daddr.second,
            buffer->daddr.third, buffer->daddr.fourth, buffer->daddr.first,
            buffer->daddr.second, buffer->daddr.third, buffer->daddr.fourth);
}
void printUDP(char * ch) {
    struct frame* buffer = (struct frame*) ch;
    struct udph* udh = (struct udph*) buffer->data;
    printf(
            "\nUDP:::::::::::::::::::::::::::::\nsPort: 0x%.4x (%d)\ndPort: 0x%.4x (%d)\nlen: 0x%.4x\ncheck: 0x%.4x\n",
            htons(udh->sPort), htons(udh->sPort), htons(udh->dPort),
            htons(udh->dPort), htons(udh->len), htons(udh->check));
}
void printIcmp(char * ch) {
    struct frame* buffer = (struct frame*) ch;
    struct icmph* icmp = (struct icmph*) buffer->data;
    printf(
            "\nICMP:::::::::::::::::::::::::::\ntype: 0x%.2x \ncode: 0x%.2x\nchecksum: 0x%.4x\nMSI: 0x%.8x\n",
            icmp->type, icmp->code, icmp->checksum, icmp->msi);
}
