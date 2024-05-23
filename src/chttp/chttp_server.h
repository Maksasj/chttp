#ifndef _CHTTP_SERVER_H_
#define _CHTTP_SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "chttp_net.h"
#include "chttp_utils.h"

#include "chttp_connection.h"
#include "chttp_request.h"
#include "chttp_response.h"

typedef CHTTPResponse* (CHTTPServerRouteCallback)(CHTTPConnection* con, CHTTPRequest* request);
typedef int (CHTTPRouteFilterCallback)(char* route, CHTTPRequest* request);

typedef struct CHTTPServerRoute {
    char* route;

    CHTTPRouteFilterCallback* filter;
    CHTTPServerRouteCallback* callback;
} CHTTPServerRoute;

typedef struct CHTTPServer {
    unsigned int port;

    struct sockaddr_in servaddr;
    int socket;

    unsigned int routesCount;
    CHTTPServerRoute* routes;

    void* userPtr;
} CHTTPServer;

CHTTPServer* chttp_new_server(unsigned int port);
void chttp_free_server(CHTTPServer* server);

CHTTPRequest* chttp_receive_request(CHTTPConnection* connection);

void chttp_route(CHTTPServer* server, char* route, CHTTPRouteFilterCallback* filter, CHTTPServerRouteCallback* callback);

void chttp_server_set_user_pointer(CHTTPServer* server, void* userPtr);
void* chttp_server_get_user_pointer(CHTTPServer* server);

void chttp_str_route(CHTTPServer* server, char* route, CHTTPServerRouteCallback* callback);
void chttp_glob_route(CHTTPServer* server, char* pattern, CHTTPServerRouteCallback* callback);

int chttp_str_route_filter(char* string, CHTTPRequest* request);
int chttp_glob_route_filter(char* route, CHTTPRequest* request);

int chttp_running(CHTTPServer* server);
void chttp_listen(CHTTPServer* server);

#endif