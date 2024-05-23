#ifndef _CHTTP_HTTP_HEADERS_H_
#define _CHTTP_HTTP_HEADERS_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "chttp_version.h"
#include "chttp_status_code.h"

typedef struct CHTTPHeaders {
    char* headers;
} CHTTPHeaders;

CHTTPHeaders* chttp_new_headers();

void chttp_add_header(CHTTPHeaders* headers, char* header);
void chttp_add_default_headers(CHTTPHeaders* headers, char* message);

void chttp_free_headers(CHTTPHeaders* headers);

#endif