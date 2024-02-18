#include "chttp/chttp.h"

HTTPResponse* index_page(HTTPConnection* con, HTTPRequest* request);
HTTPResponse* about_page(HTTPConnection* con, HTTPRequest* request);

int main() {
    HTTPServer* server = http_new_server(6969);

    http_str_route(server, "/", index_page);
    http_regex_route(server, "/.*\\out$", about_page);

    while(http_running(server)) {
        http_listen(server);
    }

    http_free_server(server);

    return 0;
}

HTTPResponse* index_page(HTTPConnection* con, HTTPRequest* request) {
    return http_ok_response_file(HTTP_1_1, "index.html");
}

HTTPResponse* about_page(HTTPConnection* con, HTTPRequest* request) {
    return http_ok_response_file(HTTP_1_1, "about.html");
}
