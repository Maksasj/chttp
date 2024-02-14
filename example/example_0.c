#include "chttp/chttp.h"

HTTPResponse* index_page(HTTPConnection* con, HTTPRequest* request);
HTTPResponse* about_page(HTTPConnection* con, HTTPRequest* request);

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

HTTPResponse* index_page(HTTPConnection* con, HTTPRequest* request) {

    return http_ok_response(HTTP_1_1, "This is index page");
}

HTTPResponse* about_page(HTTPConnection* con, HTTPRequest* request) {

    return http_ok_response(HTTP_1_1, "This is about page");
}
