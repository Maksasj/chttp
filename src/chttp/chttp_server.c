#include "chttp_server.h"

CHTTPServer* chttp_new_server(unsigned int port) {
    if ((port < 1) || (port > 65535)){
        CHTTP_LOG(CHTTP_ERROR, "Invalid port specified");
        exit(1);
    }

    CHTTPServer* server = malloc(sizeof(CHTTPServer));

    if ((server->l_socket = socket(AF_INET, SOCK_STREAM,0))< 0){
        CHTTP_LOG(CHTTP_ERROR, "Cannot create listening socket");
        exit(1);
    }

    memset(&server->servaddr, 0, sizeof(server->servaddr));
    server->servaddr.sin_family = AF_INET;
    server->servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    server->servaddr.sin_port = htons(port);

    if (bind(server->l_socket, (struct sockaddr *)&server->servaddr, sizeof(server->servaddr)) < 0){
        CHTTP_LOG(CHTTP_ERROR, "Error occurred while trying to bind listening socket");
        exit(1);
    }

    server->routes = NULL;
    server->routesCount = 0;
    server->port = port;

    CHTTP_LOG(CHTTP_INFO, "Successfully initialized HTTP server");

    return server;
}

void chttp_free_server(CHTTPServer* server) {
    free(server->routes);
    free(server);
}

void chttp_route(CHTTPServer* server, char* route, CHTTPRouteFilterCallback* filter, CHTTPServerRouteCallback* callback) {
    if(server->routesCount == 0) {
        server->routes = malloc(sizeof(CHTTPServerRoute));
        server->routesCount = 1;

        server->routes[0].route = route;
        server->routes[0].filter = filter;
        server->routes[0].callback = callback;
    } else {
        unsigned int size = (++server->routesCount) * sizeof(CHTTPServerRoute);

        server->routes = realloc(server->routes,  size);

        server->routes[server->routesCount - 1].route = route;
        server->routes[server->routesCount - 1].filter = filter;
        server->routes[server->routesCount - 1].callback = callback;
    }
}

int chttp_str_route_filter(char* route, CHTTPRequest* request) {
    return strcmp(route, request->requestUri);
}

int chttp_glob_route_filter(char* pattern, CHTTPRequest* request) {
    return glob_utf8(pattern, request->requestUri);
}

void chttp_str_route(CHTTPServer* server, char* string, CHTTPServerRouteCallback* callback) {
    chttp_route(server, string, chttp_str_route_filter, callback);

    CHTTP_LOG(CHTTP_INFO, "Added string route '%s'", string);
}

void chttp_glob_route(CHTTPServer* server, char* pattern, CHTTPServerRouteCallback* callback) {
    chttp_route(server, pattern, chttp_glob_route_filter, callback);

    CHTTP_LOG(CHTTP_INFO, "Added glob route '%s'", pattern);
}

int chttp_running(CHTTPServer* server) {
    return 1;
}

CHTTPRequest* chttp_receive_request(CHTTPConnection* connection) {
    char* buffer = (char*) malloc(HTTP_REQUEST_MAX_SIZE);

    int length = recv(connection->c_socket, buffer , HTTP_REQUEST_MAX_SIZE , 0);

    if(length == 0) {
        CHTTP_LOG(CHTTP_WARNING, "While receiving HTTP request, connection was closed");
        return NULL;
    }

    if(length < 0) {
        CHTTP_LOG(CHTTP_ERROR, "While receiving HTTP request, error occurred");
        return NULL;
    }

    CHTTPRequest* request = chttp_parse_request(buffer, length);
    free(buffer);

    return request;
}

void chttp_listen(CHTTPServer* server) {
    CHTTP_LOG(CHTTP_INFO, "Server listens for connections");

    if (listen(server->l_socket, 5) < 0){
        fprintf(stderr,"ERROR #4: error in listen().\n");
        exit(1);
    }

    CHTTPConnection* connection = chttp_accept_connection(server);

    if(connection == NULL) {
        CHTTP_LOG(CHTTP_WARNING, "Error occurred while accepting connection, closing connection");
        return;
    }

    CHTTPRequest* request = chttp_receive_request(connection);

    if(request == NULL) {
        CHTTP_LOG(CHTTP_WARNING, "Error occurred while receiving HTTP request, closing connection");
        chttp_connection_close(connection);
        chttp_free_connection(connection);
        return;
    }

    CHTTP_LOG(CHTTP_INFO, "User %s requests '%s' route", connection->ipAddress, request->requestUri);

    int found = 0;
    for(int index = 0; index < server->routesCount; ++index) {
        CHTTPServerRoute route = server->routes[index];

        if(route.filter(route.route, request) != 0) 
            continue;

        found = 1;

        CHTTPResponse* response = route.callback(connection, request);
        chttp_send_response(response, connection);
        chttp_free_response(response);
    }

    if(!found) {
        CHTTP_LOG(CHTTP_WARNING, "User requested resource not found");

        CHTTPResponse* response = chttp_not_found_response(HTTP_1_1, "404 Not found");
        chttp_send_response(response, connection);
        chttp_free_response(response);
    }

    chttp_connection_close(connection);

    chttp_free_request(request);
    chttp_free_connection(connection);

    CHTTP_LOG(CHTTP_INFO, "Closing HTTP connection");
}