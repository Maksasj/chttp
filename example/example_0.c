#include "chttp/chttp.h"

CHTTPResponse* index_page(CHTTPConnection* con, CHTTPRequest* request);
CHTTPResponse* about_page(CHTTPConnection* con, CHTTPRequest* request);

int main() {
    CHTTPServer* server = chttp_new_server(6969);

    chttp_str_route(server, "/", index_page);
    chttp_str_route(server, "/about", about_page);

    while(chttp_running(server)) {
        chttp_listen(server);
    }

    chttp_free_server(server);

    return 0;
}

CHTTPResponse* index_page(CHTTPConnection* con, CHTTPRequest* request) {
    return chttp_ok_response_file(HTTP_1_1, "index.html");
}

CHTTPResponse* about_page(CHTTPConnection* con, CHTTPRequest* request) {
    return chttp_ok_response_file(HTTP_1_1, "about.html");
}
