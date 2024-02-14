#ifndef _CHTTP_HTTP_RESPONSE_H_
#define _CHTTP_HTTP_RESPONSE_H_

#include <string.h>
#include <stdlib.h>

#include "http_version.h"

typedef enum HTTPStatusCode {
    CONTINUE = 100,                         // Continue
    SWITCHING_PROTOCOLS = 101,              // Switching Protocols

    OK = 200,                               // OK
    CREATED = 201,                          // Created
    ACCEPTED = 202,                         // Accepted
    NON_AUTHORITATIVE_INFORMATION = 203,    // Non-Authoritative Information
    NO_CONTENT = 204,                       // No Content
    RESET_CONTENT = 205,                    // Reset Content
    PARTIAL_CONTENT = 206,                  // Partial Content

    MULTIPLE_CHOICES = 300,                 // Multiple Choices
    MOVED_PERMANENTLY = 301,                // Moved Permanently
    FOUND = 302,                            // Found
    SEE_OTHER = 303,                        // See Other
    NOT_MODIFIED = 304,                     // Not Modified
    USE_PROXY = 305,                        // Use Proxy
    TEMPORARY_REDIRECT = 307,               // Temporary Redirect

    BAD_REQUEST = 400,                      // Bad Request
    UNAUTHORIZED = 401,                     // Unauthorized
    PAYMENT_REQUIRED = 402,                 // Payment Required
    FORBIDDEN = 403,                        // Forbidden
    NOT_FOUND = 404,                        // Not Found
    METHOD_NOT_ALLOWED = 405,               // Method Not Allowed
    NOT_ACCEPTABLE = 406,                   // Not Acceptable
    PROXY_AUTHENTICATION_REQUIRED = 407,    // Proxy Authentication Required
    REQUEST_TIME_OUT = 408,                 // Request Time-out
    CONFLICT = 409,                         // Conflict
    GONE = 410,                             // Gone
    LENGTH_REQUIRED = 411,                  // Length Required
    PRECONDITION_FAILED = 412,              // Precondition Failed
    REQUEST_ENTITY_TOO_LARGE = 413,         // Request Entity Too Large
    REQUEST_URI_TOO_LARGE = 414,            // Request-URI Too Large
    UNSUPPORTED_MEDIA_TYPE = 415,           // Unsupported Media Type
    REQUESTED_RANGE_NOT_SATISFIABLE = 416,  // Requested range not satisfiable
    EXPECTATION_FAILED = 417,               // Expectation Failed

    INTERNAL_SERVER_ERROR = 500,            // Internal Server Error
    NOT_IMPLEMENTED = 501,                  // Not Implemented
    BAD_GATEWAY = 502,                      // Bad Gateway
    SERVICE_UNAVAILABLE = 503,              // Service Unavailable
    GATEWAY_TIME_OUT = 504,                 // Gateway Time-out
    HTTP_VERSION_NOT_SUPPORTED = 505,       // HTTP Version not supported
} HTTPStatusCode;

typedef struct HTTPResponse {
    HTTPVersion version;
    HTTPStatusCode code;

    char* headers;
    char* message;
} HTTPResponse;

char* http_stringify_version(HTTPVersion version);
char* http_stringify_status(HTTPStatusCode code);
char* http_stringify_response(HTTPResponse* response);

HTTPResponse* http_response(HTTPVersion version, HTTPStatusCode code, char* headers, char* message);
HTTPResponse* http_ok_response(HTTPVersion version, char* message);

void http_free_response(HTTPResponse* response);

#endif