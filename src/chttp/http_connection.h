#ifndef _CHTTP_CONNECTION_H_
#define _CHTTP_CONNECTION_H_

#include "chttp_net.h"
#include "chttp_utils.h"

#include "http_request.h"
#include "http_response.h"

struct HTTPServer;

typedef struct HTTPConnection {
    int c_socket;

    struct sockaddr_in clientaddr;
    socklen_t clientaddrlen;
} HTTPConnection;

HTTPConnection* http_accept_connection(struct HTTPServer* server);

#endif