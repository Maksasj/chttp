#ifndef _CHTTP_HTTP_REQUEST_H_
#define _CHTTP_HTTP_REQUEST_H_

#include "http_version.h"
#include "http_method.h"

typedef struct HTTPRequest {
    // Request-Line
    HTTPMethod method;
    HTTPVersion version;
    char* requestUri;

    // Headers
    char* headers;

    // Message-body
    char* message;
} HTTPRequest;

HTTPRequest* http_parse_request(char* string);

void http_free_request(HTTPRequest* request);

#endif