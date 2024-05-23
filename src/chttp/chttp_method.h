#ifndef _CHTTP_HTTP_METHOD_H_
#define _CHTTP_HTTP_METHOD_H_

#include <stdlib.h>
#include <string.h>

typedef enum CHTTPMethod {
    GET
} CHTTPMethod;

CHTTPMethod chttp_unstringify_method(char* string);
char* chttp_stringify_method(CHTTPMethod);

#endif