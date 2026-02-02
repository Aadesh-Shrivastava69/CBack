#include "collections.h"
#include "net.h"

#include <stdio.h>

int main() {
    cback_hash_map *hm = cback_hashmap_create(1000, sizeof(int), sizeof(cback_net_conn));

    cback_net_conn net = net_connect(NULL, "youtube.com", "80");
    cback_hash_map_put(hm, &net.sock_fd, &net);

    cback_net_conn net2 = net_connect(NULL, "youtube.com", "80");
    cback_hash_map_put(hm, &net2.sock_fd, &net2);

    cback_net_conn net3 = net_connect(NULL, "youtube.com", "80");
    cback_hash_map_put(hm, &net3.sock_fd, &net3);

    cback_hash_node g_net;
    cback_hash_map_get(hm, &net3.sock_fd, &g_net);

    printf("Looked for %d\n", net3.sock_fd);
    printf("Got key: %d, value.fd: %d\n", *(int *)g_net.key, ((cback_net_conn *)g_net.value)->sock_fd);
}
