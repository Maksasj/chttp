#include "chttp.h"

HTTPServer* http_new(unsigned int port) {
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

    return server;
}

void http_free(HTTPServer* server) {
    free(server);
}

void http_route(HTTPServer* server, const char* route, void(*callback)(HTTPConnection* con, HTTPRequest* request)) {

}

int http_running(HTTPServer* server) {
    return 1;
}

HTTPConnection* http_accept_connection(HTTPServer* server) {
    HTTPConnection* connection = malloc(sizeof(HTTPConnection));

    memset(&connection->clientaddr,0, sizeof(connection->clientaddr));

    connection->clientaddrlen = sizeof(struct sockaddr);
    if ((connection->c_socket = accept(server->l_socket,(struct sockaddr*)&connection->clientaddr,&connection->clientaddrlen)) < 0){
        fprintf(stderr,"ERROR #5: error occured accepting connection.\n");
        exit(1);
    }

    return connection;
}

void http_listen(HTTPServer* server) {
    char buffer[1024];
    char response[] = "HTTP/1.1 200 OK\r\nContent-Length: 20\r\nConnection: close\r\n\r\nHello, world from C!";

    if (listen(server->l_socket, 5) < 0){
        fprintf(stderr,"ERROR #4: error in listen().\n");
        exit(1);
    }

    HTTPConnection* connection = http_accept_connection(server);

    int s_len = recv(connection->c_socket,buffer,sizeof(buffer),0);
    int r_len = send(connection->c_socket,response, sizeof(response),0);

    printf("IP: %s Sent: %d Received: %d\n",inet_ntoa(connection->clientaddr.sin_addr),s_len, r_len);

    close(connection->c_socket);
    free(connection);
}