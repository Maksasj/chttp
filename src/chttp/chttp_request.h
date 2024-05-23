#ifndef _CHTTP_HTTP_REQUEST_H_
#define _CHTTP_HTTP_REQUEST_H_

#include <stdio.h>

#include "chttp_version.h"
#include "chttp_method.h"

#define HTTP_REQUEST_MAX_SIZE 8192

typedef struct CHTTPRequest {
    // Request-Line
    CHTTPMethod method;
    CHTTPVersion version;
    char* requestUri;

    // Headers
    char* headers;

    // Message-body
    char* message;
} CHTTPRequest;

void chttp_parse_request_line(CHTTPRequest* request, char* line);

CHTTPRequest* chttp_parse_request(char* buffer, unsigned int length);
void chttp_free_request(CHTTPRequest* request);

#endif