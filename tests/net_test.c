#include "net.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    cback_net_loop loop = cback_net_loop_init(12);
    cback_net_conn *net = cback_net_connect(&loop, "monkeytype.com", "80");
    if (net->state != NET_CONNECTING) {
        perror("");
        exit(EXIT_FAILURE);
    }

    printf("Successfully waiting for connection!!!\n");
    while (1) {
        if (net->state == NET_CONNECTED) {
            printf("Connected successfully!!!\n");
            exit(EXIT_SUCCESS);
        }

        cback_net_loop_poll(&loop, 100);
    }
}
