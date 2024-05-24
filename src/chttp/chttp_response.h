#ifndef _CHTTP_HTTP_RESPONSE_H_
#define _CHTTP_HTTP_RESPONSE_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "chttp_net.h"

#include "chttp_headers.h"
#include "chttp_version.h"
#include "chttp_status_code.h"

#include "chttp_connection.h"

typedef struct CHTTPResponse {
    CHTTPVersion version;
    HTTPStatusCode code;

    char* headers;
    char* message;
} CHTTPResponse;

CHTTPResponse* chttp_response(CHTTPVersion version, HTTPStatusCode code, CHTTPHeaders* headers, char* message);

CHTTPResponse* chttp_ok_response(CHTTPVersion version, char* message);
CHTTPResponse* chttp_ok_response_file(CHTTPVersion version, char* fileName);

CHTTPResponse* chttp_not_found_response(CHTTPVersion version, char* message);

unsigned long long chttp_calculate_string_response_size(CHTTPResponse* response);
char* chttp_stringify_response(CHTTPResponse* response);

void chttp_send_response(CHTTPResponse* response, CHTTPConnection* connection);

void chttp_free_response(CHTTPResponse* response);

#endif