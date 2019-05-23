#include"head.h"
int main() {
    int res;
    puts(
            "API CLIENT SERVER UDP STARS\nProgram created by Chris Swidrak (Military University of Technology, Warsaw)");

    pthread_mutex_init(&counter_lock, NULL);
    res = pthread_create(&server_t, NULL, server_thread, NULL);
    if (res != 0)
        perror("#Cannot create server Thread!");
    res = pthread_create(&client_t, NULL, client_thread, NULL);
    if (res != 0)
        perror("#Cannot create client Thread!");
    res = pthread_join(server_t, NULL);
    if (res != 0)
        perror("#Cannot join server Thread!");
    res = pthread_join(client_t, NULL);
    if (res != 0)
        perror("#Cannot join client Thread!");
    pthread_mutex_destroy(&counter_lock);

    return 0;
}
