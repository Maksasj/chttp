#ifndef _CHTTP_H_
#define _CHTTP_H_

#ifdef _WIN32
    #include <winsock2.h>
    #define socklen_t int
#else
    #include <sys/socket.h>
    #include <sys/types.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "http_request.h"
#include "http_response.h"

typedef struct HTTPConnection {
    int c_socket;

    struct sockaddr_in clientaddr;
    socklen_t clientaddrlen;
} HTTPConnection;

typedef HTTPResponse* (HTTPServerRouteCallback)(HTTPConnection* con, HTTPRequest* request);

typedef struct HTTPServerRoute {
    char* route;
    HTTPServerRouteCallback* callback;
} HTTPServerRoute;

typedef struct HTTPServer {
    unsigned int port;

    struct sockaddr_in servaddr;
    int l_socket;

    unsigned int routesCount;
    HTTPServerRoute* routes;
} HTTPServer;

HTTPServer* http_new(unsigned int port);
void http_free(HTTPServer* server);

void http_route(HTTPServer* server, char* route, HTTPServerRouteCallback* callback);
int http_running(HTTPServer* server);
void http_listen(HTTPServer* server);

#endif