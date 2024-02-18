#ifndef _CHTTP_SERVER_H_
#define _CHTTP_SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "chttp_net.h"
#include "chttp_utils.h"

#include "http_connection.h"
#include "http_request.h"
#include "http_response.h"

typedef HTTPResponse* (HTTPServerRouteCallback)(HTTPConnection* con, HTTPRequest* request);
typedef int (HTTPRouteFilterCallback)(char* route, HTTPRequest* request);

typedef struct HTTPServerRoute {
    char* route;

    HTTPRouteFilterCallback* filter;
    HTTPServerRouteCallback* callback;
} HTTPServerRoute;

typedef struct HTTPServer {
    unsigned int port;

    struct sockaddr_in servaddr;
    int l_socket;

    unsigned int routesCount;
    HTTPServerRoute* routes;
} HTTPServer;

HTTPServer* http_new_server(unsigned int port);
void http_free_server(HTTPServer* server);

HTTPRequest* http_receive_request(HTTPConnection* connection);

void http_route(HTTPServer* server, char* route, HTTPRouteFilterCallback* filter, HTTPServerRouteCallback* callback);

void http_str_route(HTTPServer* server, char* route, HTTPServerRouteCallback* callback);
void http_glob_route(HTTPServer* server, char* pattern, HTTPServerRouteCallback* callback);

int http_str_route_filter(char* string, HTTPRequest* request);
int http_glob_route_filter(char* route, HTTPRequest* request);

int http_running(HTTPServer* server);
void http_listen(HTTPServer* server);

#endif