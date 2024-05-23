#ifndef _CHTTP_UTILS_H_
#define _CHTTP_UTILS_H_

#include <stdio.h>
#include <stdarg.h>

/*
#define GLOB_IMPLEMENTATION
#include "glob.h"
*/

typedef enum CHTTPLogLevel {
    CHTTP_INFO,
    CHTTP_WARNING,
    CHTTP_ERROR
} CHTTPLogLevel;

char* chttp_stringify_log_level(CHTTPLogLevel logLevel);

void chttp_log(CHTTPLogLevel logLevel, const char *format, ...);

#define CHTTP_LOG(logLevel, ...) chttp_log(logLevel, __VA_ARGS__)

// Forward declaration of glob enum and glob_utf8 function
typedef enum {
    GLOB_OOM_ERROR      = -4,
    GLOB_ENCODING_ERROR = -3,
    GLOB_SYNTAX_ERROR   = -2,
    GLOB_UNMATCHED      = -1,
    GLOB_MATCHED        =  0,
} Glob_Result;

Glob_Result glob_utf8(const char *pattern, const char *text);

#endif