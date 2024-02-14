#ifndef _CHTTP_HTTP_METHOD_H_
#define _CHTTP_HTTP_METHOD_H_

#include <stdlib.h>
#include <string.h>

typedef enum HTTPMethod {
    GET
} HTTPMethod;

HTTPMethod http_unstringify_method(char* string);

#endif