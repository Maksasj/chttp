#ifndef _CHTTP_CONNECTION_H_
#define _CHTTP_CONNECTION_H_

#include "chttp_net.h"
#include "chttp_utils.h"

struct CHTTPServer;

typedef struct CHTTPConnection {
    int c_socket;

    struct sockaddr_in clientaddr;
    char ipAddress[INET_ADDRSTRLEN];
    socklen_t clientaddrlen;
} CHTTPConnection;

CHTTPConnection* chttp_accept_connection(struct CHTTPServer* server);
void chttp_free_connection(CHTTPConnection* connection);

void chttp_connection_close(CHTTPConnection* connection);

#endif