#ifndef NET_H
#define NET_H

#include "utils.h"

#include <sys/socket.h>

typedef enum {
    NET_OK = 0,
    NET_CONNECTING,
    NET_CONNECTED,
    NET_DISCONNECTED,

    NET_SOCK_UNINIT = -1,
} cback_net_state;

typedef struct cback_net_conn{
    int sock_fd;
    cback_net_state state;

    struct cback_net_conn *next;
} cback_net_conn;

// NOTE: Current implementation uses an array
//       A HashMap is preffered ("collections.h")
typedef struct {
    int epoll_fd;

    cback_net_conn *connections;
    u32 count;
} cback_net_loop;

cback_net_conn cback_net_connect(cback_net_loop *loop, const char *host, const char *port);

#endif
