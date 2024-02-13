#include "chttp/chttp.h"

void index_page(HTTPConnection* con, HTTPRequest* request);
void about_page(HTTPConnection* con, HTTPRequest* request);

int main() {
    HTTPServer* server = http_new(6969);

    http_route(server, "/", index_page);
    http_route(server, "/about", about_page);

    while(http_running(server)) {
        http_listen(server);
    }

    http_free(server);

    return 0;
}

void index_page(HTTPConnection* con, HTTPRequest* request) {

}

void about_page(HTTPConnection* con, HTTPRequest* request) {

}
