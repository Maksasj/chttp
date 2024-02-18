#ifndef _CHTTP_UTILS_H_
#define _CHTTP_UTILS_H_

#include <stdio.h>
#include <stdarg.h>

typedef enum CHTTP_LOG_LEVEL {
    SERVER_INFO,
    SERVER_WARNING,
    SERVER_ERROR
} CHTTP_LOG_LEVEL;

char* chttp_stringify_log_level(CHTTP_LOG_LEVEL logLevel);

void chttp_log(CHTTP_LOG_LEVEL logLevel, const char *format, ...);

#define CHTTP_LOG(logLevel, ...) chttp_log(logLevel, __VA_ARGS__)

#endif