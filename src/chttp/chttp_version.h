#ifndef _CHTTP_HTTP_VERSION_H_
#define _CHTTP_HTTP_VERSION_H_

#include <stdlib.h>
#include <string.h>

#include "chttp_utils.h"

typedef enum CHTTPVersion {
    HTTP_1_1
} CHTTPVersion;

char* chttp_stringify_version(CHTTPVersion version);
CHTTPVersion chttp_unstringify_version(char* string);

#endif