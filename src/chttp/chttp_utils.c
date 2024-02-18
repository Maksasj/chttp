#include "chttp_utils.h"

char* chttp_stringify_log_level(CHTTP_LOG_LEVEL logLevel) {
    switch (logLevel) {
        case SERVER_INFO:       { return "INFO"; }
        case SERVER_WARNING:    { return "WARNING"; }
        case SERVER_ERROR:      { return "ERROR"; }
    }

    return NULL;
}

void chttp_log(CHTTP_LOG_LEVEL logLevel, const char *format, ...) {
    va_list args;
    va_start(args, format);

    printf("[%s] ", chttp_stringify_log_level(logLevel));
    vprintf(format, args);
    printf("\n");

    va_end(args);
}
