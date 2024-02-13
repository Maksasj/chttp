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

}

void http_route(HTTPServer* server, const char* route, void(*callback)(HTTPRequest* request)) {

}

int http_running(HTTPServer* server) {

}

void http_listen(HTTPServer* server) {
    int c_socket; // prisijungusio kliento socket'as

    struct sockaddr_in clientaddr; // Prisijungusio kliento adreso struktūra
    socklen_t clientaddrlen;

    char buffer[1024];

    /*
    * Nurodoma, kad socket'u l_socket bus laukiama klientų prisijungimo,
    * eilėje ne daugiau kaip 5 aptarnavimo laukiantys klientai
    */
    if (listen(server->l_socket, 5) < 0){
        fprintf(stderr,"ERROR #4: error in listen().\n");
        exit(1);
    }

    for(;;){
        memset(&clientaddr,0, sizeof(clientaddr));
        memset(&buffer,0,sizeof(buffer));

        clientaddrlen = sizeof(struct sockaddr);
        if ((c_socket = accept(server->l_socket,(struct sockaddr*)&clientaddr,&clientaddrlen)) < 0){
            fprintf(stderr,"ERROR #5: error occured accepting connection.\n");
            exit(1);
        }

        int s_len = recv(c_socket,buffer,sizeof(buffer),0);

        char response[] = "HTTP/1.1 200 OK\r\nContent-Length: 20\r\nConnection: close\r\n\r\nHello, world from C!";
        int r_len = send(c_socket,response, sizeof(response),0);

        printf("IP: %s Sent: %d Received: %d\n",inet_ntoa(clientaddr.sin_addr),s_len, r_len);

        close(c_socket);
    }
}