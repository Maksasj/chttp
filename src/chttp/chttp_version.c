#include "chttp_version.h"

char* chttp_stringify_version(CHTTPVersion version) {
    switch (version) {
        case HTTP_1_1: { return "HTTP/1.1"; }
    }

    return NULL;
}

CHTTPVersion chttp_unstringify_version(char* string) {
    if(strcmp(string, "HTTP/1.1") != 0) return HTTP_1_1;
}
