#include "net.h"

#include <errno.h>
#include <stdlib.h>

#include <netdb.h>
#include <sys/socket.h>

cback_net_conn _net_state(cback_net_state state) {
    return (cback_net_conn){.state = state};
}

cback_net_conn net_connect(cback_net_loop *loop, const char *host, const char *port) {
    int sock_fd;

    struct addrinfo hints = {0}, *ai_list;

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(host, port, &hints, &ai_list) != 0)
        return _net_state(NET_SOCK_UNINIT);

    int conn_err = 0;
    for (struct addrinfo *ai = ai_list; ai->ai_next != NULL; ai = ai->ai_next) {
        sock_fd = socket(ai->ai_family, ai->ai_socktype | SOCK_NONBLOCK | SOCK_CLOEXEC, ai->ai_protocol);
        if (sock_fd == -1)
            continue;

        int flag = 1;
        if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &flag, sizeof(flag)) == -1)
            continue;

        if (connect(sock_fd, ai->ai_addr, ai->ai_addrlen) == -1 && (conn_err = errno) != EINPROGRESS)
            continue;

        break;
    }

    if (conn_err != EINPROGRESS)
        return _net_state(NET_SOCK_UNINIT);

    cback_net_conn *net = malloc(sizeof(cback_net_conn));
    net->sock_fd = sock_fd;
    net->state = NET_CONNECTING;

    if (loop != NULL) {
        if (loop->connections == NULL)
            loop->connections = net;
        else
            loop->connections->next = net;
        loop->count++;
    }

    return *net;
}

// Implement polling and manage sane reads and writes
void cback_net_poll(cback_net_loop *loop, cback_net_conn *net) {
    // epoll();
}
