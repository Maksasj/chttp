#include "http_connection.h"

#include "http_server.h"

HTTPConnection* http_accept_connection(struct HTTPServer* server) {
    HTTPConnection* connection = malloc(sizeof(HTTPConnection));
    memset(&connection->clientaddr, 0, sizeof(connection->clientaddr));

    connection->clientaddrlen = sizeof(struct sockaddr);
    
    if ((connection->c_socket = accept(server->l_socket, (struct sockaddr*)&connection->clientaddr,&connection->clientaddrlen)) < 0){
        free(connection);
        return NULL;
    }

    struct sockaddr_in *ipv4 = (struct sockaddr_in *) (struct sockaddr*) (void*) &connection->clientaddr;
    inet_ntop(AF_INET, &(ipv4->sin_addr), connection->ipAddress, INET_ADDRSTRLEN);

    CHTTP_LOG(SERVER_INFO, "Successfully accepted connection from %s", connection->ipAddress);

    return connection;
}

void chttp_free_connection(HTTPConnection* connection) {
    free(connection);
}

void chttp_connection_close(HTTPConnection* connection) {
    close(connection->c_socket);
}
