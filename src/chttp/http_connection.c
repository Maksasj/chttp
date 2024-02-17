#include "http_connection.h"

#include "http_server.h"

HTTPConnection* http_accept_connection(struct HTTPServer* server) {
    HTTPConnection* connection = malloc(sizeof(HTTPConnection));

    memset(&connection->clientaddr, 0, sizeof(connection->clientaddr));

    connection->clientaddrlen = sizeof(struct sockaddr);
    if ((connection->c_socket = accept(server->l_socket,(struct sockaddr*)&connection->clientaddr,&connection->clientaddrlen)) < 0){
        fprintf(stderr,"ERROR #5: error occured accepting connection.\n");
        exit(1);
    }

    return connection;
}
