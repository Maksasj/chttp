#include "chttp_connection.h"

#include "chttp_server.h"

CHTTPConnection* chttp_accept_connection(struct CHTTPServer* server) {
    CHTTPConnection* connection = malloc(sizeof(CHTTPConnection));
    memset(&connection->clientaddr, 0, sizeof(connection->clientaddr));

    connection->clientaddrlen = sizeof(struct sockaddr);
    
    if ((connection->socket = accept(server->socket, (struct sockaddr*)&connection->clientaddr,&connection->clientaddrlen)) < 0){
        free(connection);
        return NULL;
    }

    struct sockaddr_in *ipv4 = (struct sockaddr_in *) (struct sockaddr*) (void*) &connection->clientaddr;
    inet_ntop(AF_INET, &(ipv4->sin_addr), connection->ipAddress, INET_ADDRSTRLEN);

    CHTTP_LOG(CHTTP_INFO, "Successfully accepted connection from %s", connection->ipAddress);

    connection->server = server;

    return connection;
}

void chttp_free_connection(CHTTPConnection* connection) {
    free(connection);
}

void chttp_connection_close(CHTTPConnection* connection) {
    close(connection->socket);
}
