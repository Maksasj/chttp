#include "chttp_method.h"

CHTTPMethod chttp_unstringify_method(char* string) {
    if(strcmp(string, "GET") == 0) return GET;
}

char* chttp_stringify_method(CHTTPMethod method) {
    if(method == GET)
        return "GET";
    
    return "Not implemented";
}