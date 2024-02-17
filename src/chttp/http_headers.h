#ifndef _CHTTP_HTTP_HEADERS_H_
#define _CHTTP_HTTP_HEADERS_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "http_version.h"
#include "http_status_code.h"

typedef struct HTTPHeaders {
    char* headers;
} HTTPHeaders;

HTTPHeaders* http_new_headers();

void http_add_header(HTTPHeaders* headers, char* header);
void http_add_default_headers(HTTPHeaders* headers, char* message);

void http_free_headers(HTTPHeaders* headers);

#endif