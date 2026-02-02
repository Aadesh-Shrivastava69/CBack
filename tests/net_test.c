#include "net.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    cback_net_conn net = cback_net_connect(NULL, "youtube.com", "80");
    if (net.state != NET_CONNECTING) {
        perror("");
        exit(EXIT_FAILURE);
    }

    printf("Successfully waiting for connection!!!\n");
}
