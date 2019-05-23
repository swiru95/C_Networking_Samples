#include "head.h"

int main(int argc, char*argv[]) {
    puts(
            "Uruchamianie odbierania ramek Ethernet\nProgram created by Chris Swidrak (Military University of Technology, Warsaw)");

    errno = pthread_create(&s_thread, NULL, sniffThread, NULL);
    errno = pthread_create(&c_thread, NULL, cThread, NULL);
    errno = pthread_join(s_thread, NULL);
    errno = pthread_join(c_thread, NULL);

    return 0;
}

