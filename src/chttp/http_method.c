#include "http_method.h"

HTTPMethod http_unstringify_method(char* string) {
    if(strcmp(string, "GET") == 0) return GET;
}

char* http_stringify_method(HTTPMethod method) {
    if(method == GET)
        return "GET";
    
    return "Not implemented";
}