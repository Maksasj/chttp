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

typedef struct HTTPRequest {

} HTTPRequest;

typedef struct HTTPResponse {

} HTTPResponse;

typedef struct HTTPServer {

} HTTPServer;

HTTPServer* http_new(int port);
void http_free(HTTPServer* server);

void http_route(HTTPServer* server, const char* route, void(*callback)(HTTPRequest* request));
int http_running(HTTPServer* server);
void http_listen(HTTPServer* server);

HTTPServer* http_new(int port) {

}

void http_free(HTTPServer* server) {

}

void http_route(HTTPServer* server, const char* route, void(*callback)(HTTPRequest* request)) {

}

int http_running(HTTPServer* server) {

}

void http_listen(HTTPServer* server) {

}

#endif