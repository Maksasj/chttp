#ifndef _CHTTP_HTTP_REQUEST_H_
#define _CHTTP_HTTP_REQUEST_H_

#include <stdio.h>

#include "http_version.h"
#include "http_method.h"

#define HTTP_REQUEST_MAX_SIZE 8192

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

void http_parse_request_line(HTTPRequest* request, char* line);
HTTPRequest* http_parse_request(char* buffer, unsigned int length);

void http_free_request(HTTPRequest* request);

#endif