#ifndef _CHTTP_HTTP_RESPONSE_H_
#define _CHTTP_HTTP_RESPONSE_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "http_headers.h"
#include "http_version.h"
#include "http_status_code.h"

typedef struct HTTPResponse {
    HTTPVersion version;
    HTTPStatusCode code;

    char* headers;
    char* message;
} HTTPResponse;

HTTPResponse* http_response(HTTPVersion version, HTTPStatusCode code, HTTPHeaders* headers, char* message);

HTTPResponse* http_ok_response(HTTPVersion version, char* message);
HTTPResponse* http_ok_response_file(HTTPVersion version, char* fileName);

unsigned long long calculate_string_response_length(HTTPResponse* response);
char* http_stringify_response(HTTPResponse* response);

void http_free_response(HTTPResponse* response);

#endif