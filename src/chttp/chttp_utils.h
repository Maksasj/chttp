#ifndef _CHTTP_UTILS_H_
#define _CHTTP_UTILS_H_

#include <stdio.h>
#include <stdarg.h>

#include "glob.h"

typedef enum CHTTP_LOG_LEVEL {
    SERVER_INFO,
    SERVER_WARNING,
    SERVER_ERROR
} CHTTP_LOG_LEVEL;

char* chttp_stringify_log_level(CHTTP_LOG_LEVEL logLevel);

void chttp_log(CHTTP_LOG_LEVEL logLevel, const char *format, ...);

#define CHTTP_LOG(logLevel, ...) chttp_log(logLevel, __VA_ARGS__)

/*
// Forward declaration of glob enum and glob_utf8 function
typedef enum {
    GLOB_OOM_ERROR      = -4,
    GLOB_ENCODING_ERROR = -3,
    GLOB_SYNTAX_ERROR   = -2,
    GLOB_UNMATCHED      = -1,
    GLOB_MATCHED        =  0,
} Glob_Result;
*/
// Glob_Result glob_utf8(const char *pattern, const char *text);

#endif