#ifndef _CHTTP_HTTP_VERSION_H_
#define _CHTTP_HTTP_VERSION_H_

#include <stdlib.h>
#include <string.h>

typedef enum HTTPVersion {
    HTTP_1_1
} HTTPVersion;

char* http_stringify_version(HTTPVersion version);
HTTPVersion http_unstringify_version(char* string);

#endif