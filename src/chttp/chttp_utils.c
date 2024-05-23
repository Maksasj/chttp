#include "chttp_utils.h"

char* chttp_stringify_log_level(CHTTPLogLevel logLevel) {
    switch (logLevel) {
        case CHTTP_INFO:       { return "INFO"; }
        case CHTTP_WARNING:    { return "WARNING"; }
        case CHTTP_ERROR:      { return "ERROR"; }
    }

    return NULL;
}

void chttp_log(CHTTPLogLevel logLevel, const char *format, ...) {
    va_list args;
    va_start(args, format);

    printf("[%s] ", chttp_stringify_log_level(logLevel));
    vprintf(format, args);
    printf("\n");

    va_end(args);
}
