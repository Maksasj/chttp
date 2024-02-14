#include "http_version.h"

char* http_stringify_version(HTTPVersion version) {
    switch (version) {
        case HTTP_1_1: { return "HTTP/1.1"; }
    }

    return NULL;
}
