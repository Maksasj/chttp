#include "http_server.h"

HTTPServer* http_new_server(unsigned int port) {
    if ((port < 1) || (port > 65535)){
        printf("ERROR #1: invalid port specified.\n");
        exit(1);
    }

    #ifdef _WIN32
        WSADATA data;
        WSAStartup(MAKEWORD(2,2),&data);
    #endif

    HTTPServer* server = malloc(sizeof(HTTPServer));

    if ((server->l_socket = socket(AF_INET, SOCK_STREAM,0))< 0){
        fprintf(stderr,"ERROR #2: cannot create listening socket.\n");
        exit(1);
    }

    memset(&server->servaddr,0, sizeof(server->servaddr));
    server->servaddr.sin_family = AF_INET;
    server->servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    server->servaddr.sin_port = htons(port);

    if (bind (server->l_socket, (struct sockaddr *)&server->servaddr,sizeof(server->servaddr))<0){
        fprintf(stderr,"ERROR #3: bind listening socket.\n");
        exit(1);
    }

    server->routes = NULL;
    server->routesCount = 0;
    server->port = port;

    CHTTP_LOG(SERVER_INFO, "Successfully initialized HTTP server");

    return server;
}

void http_free_server(HTTPServer* server) {
    free(server->routes);
    free(server);
}

void http_route(HTTPServer* server, char* route, HTTPRouteFilterCallback* filter, HTTPServerRouteCallback* callback) {
    if(server->routesCount == 0) {
        server->routes = malloc(sizeof(HTTPServerRoute));
        server->routesCount = 1;

        server->routes[0].route = route;
        server->routes[0].filter = filter;
        server->routes[0].callback = callback;
    } else {
        unsigned int size = (++server->routesCount) * sizeof(HTTPServerRoute);

        server->routes = realloc(server->routes,  size);

        server->routes[server->routesCount - 1].route = route;
        server->routes[server->routesCount - 1].filter = filter;
        server->routes[server->routesCount - 1].callback = callback;
    }
}

int http_str_route_filter(char* route, HTTPRequest* request) {
    return strcmp(route, request->requestUri);
}

int http_glob_route_filter(char* pattern, HTTPRequest* request) {
    return glob_utf8(pattern, request->requestUri);
}

void http_str_route(HTTPServer* server, char* string, HTTPServerRouteCallback* callback) {
    http_route(server, string, http_str_route_filter, callback);

    CHTTP_LOG(SERVER_INFO, "Added string route '%s'", string);
}

void http_glob_route(HTTPServer* server, char* pattern, HTTPServerRouteCallback* callback) {
    http_route(server, pattern, http_glob_route_filter, callback);

    CHTTP_LOG(SERVER_INFO, "Added glob route '%s'", pattern);
}

int http_running(HTTPServer* server) {
    return 1;
}

HTTPRequest* http_receive_request(HTTPConnection* connection) {
    #define HTTP_REQUEST_MAX_SIZE 8192

    char* buffer = malloc(HTTP_REQUEST_MAX_SIZE);

    int received = recv(connection->c_socket, buffer , HTTP_REQUEST_MAX_SIZE , 0);

    HTTPRequest* request = http_parse_request(buffer);
    free(buffer);

    return request;
}

void http_listen(HTTPServer* server) {
    if (listen(server->l_socket, 5) < 0){
        fprintf(stderr,"ERROR #4: error in listen().\n");
        exit(1);
    }

    HTTPConnection* connection = http_accept_connection(server);
    HTTPRequest* request = http_receive_request(connection);

    CHTTP_LOG(SERVER_INFO, "User requests '%s' route", request->requestUri);

    int found = 0;

    for(int index = 0; index < server->routesCount; ++index) {
        HTTPServerRoute route = server->routes[index];

        if(route.filter(route.route, request) != 0) continue;

        found = 1;

        HTTPResponse* response = route.callback(connection, request);
        http_send_response(response, connection->c_socket, 0);
        http_free_response(response);
    }

    if(!found) {
        CHTTP_LOG(SERVER_WARNING, "User requested resource not found");

        HTTPResponse* response = http_not_found_response(HTTP_1_1, "404 Not found");
        http_send_response(response, connection->c_socket, 0);
        http_free_response(response);
    }

    http_free_request(request);

    close(connection->c_socket);
    free(connection);
}