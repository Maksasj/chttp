#include "chttp_headers.h"

CHTTPHeaders* chttp_new_headers() {
    CHTTPHeaders* headers = malloc(sizeof(CHTTPHeaders));

    headers->headers = NULL;

    return headers;
}

void chttp_add_header(CHTTPHeaders* headers, char* header) {
    if(headers->headers == NULL) {
        headers->headers = malloc(strlen(header) + 3);
        strcpy(headers->headers, header);
        strcat(headers->headers, "\r\n");
    } else {
        unsigned int size = strlen(headers->headers) + strlen(header) + 3;
        headers->headers = realloc(headers->headers, size);

        strcat(headers->headers, header);
        strcat(headers->headers, "\r\n");
    }
}

void chttp_add_default_headers(CHTTPHeaders* headers, char* message) {
    unsigned int size = strlen(message);
    int contentLengthNumberLength = snprintf( NULL, 0, "%d", size);

    char *contentLengthHeader = malloc(17 + contentLengthNumberLength);
    sprintf(contentLengthHeader, "Content-Length: %d", size);
    chttp_add_header(headers, contentLengthHeader);
    free(contentLengthHeader);

    chttp_add_header(headers, "Connection: close");
}

void chttp_free_headers(CHTTPHeaders* headers) {
    free(headers->headers);
    free(headers);
}