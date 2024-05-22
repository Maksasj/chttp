#ifndef _CHTTP_CONNECTION_H_
#define _CHTTP_CONNECTION_H_

#include "chttp_net.h"
#include "chttp_utils.h"

struct HTTPServer;

typedef struct HTTPConnection {
    int c_socket;

    struct sockaddr_in clientaddr;
    char ipAddress[INET_ADDRSTRLEN];
    socklen_t clientaddrlen;
} HTTPConnection;

HTTPConnection* http_accept_connection(struct HTTPServer* server);
void chttp_free_connection(HTTPConnection* connection);

void chttp_connection_close(HTTPConnection* connection);

#endif